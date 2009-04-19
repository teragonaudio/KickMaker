/*
 *  cBitmapFontEditable.cpp
 *  KickMaker
 *
 *  Created by Nik Reiman on 06.04.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __cBitmapFontEditable_H
#include "cBitmapFontEditable.h"
#endif

#if WINDOWS
#include <windows.h>

#if PLUGGUI
extern HINSTANCE ghInst;
inline HINSTANCE GetInstance() { return ghInst; }
#else
extern void* hInstance;
inline HINSTANCE GetInstance() { return (HINSTANCE)hInstance; }
#endif

extern long standardFontSize [];
extern const char *standardFontName [];

#ifdef STRICT
#define WINDOWSPROC WNDPROC
#else
#define WINDOWSPROC FARPROC
#endif

static WINDOWSPROC oldWndProcEdit;
LONG_PTR WINAPI WindowProcEdit (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
LONG_PTR WINAPI WindowProcEdit (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {	
	switch(message) {
		case WM_GETDLGCODE:
    {
			long flags = DLGC_WANTALLKEYS;
			return flags;
		}
		case WM_KEYDOWN:
    {
			if(wParam == VK_RETURN) {
				cBitmapFontEditable *control = (cBitmapFontEditable*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
				if(control) {
					control->bWasReturnPressed = true;
					control->looseFocus();
				}
			}
		}
      break;
      
		case WM_KILLFOCUS:
		{
			cBitmapFontEditable *control = (cBitmapFontEditable*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			if(control) {
				control->looseFocus();
      }
		} break;
	}
  
	return CallWindowProc(oldWndProcEdit, hwnd, message, wParam, lParam);
}
#endif

#if MACX
static EventHandlerRef gEventHandler = 0;
pascal OSStatus TextControlProc(EventHandlerCallRef inHandlerCallRef,
                                EventRef inEvent, void *inUserData);
pascal OSStatus TextControlProc(EventHandlerCallRef inHandlerCallRef,
                                EventRef inEvent, void *inUserData) {
	OSStatus result = eventNotHandledErr;
	UInt32 eventClass = GetEventClass(inEvent);
	UInt32 eventKind = GetEventKind(inEvent);
	cBitmapFontEditable* control = (cBitmapFontEditable*)inUserData;
  
	switch(eventClass) {
		case kEventClassKeyboard:
		{
			switch(eventKind) {
				case kEventRawKeyDown:
				case kEventRawKeyRepeat:
				{
					char macCharCode;
					UInt32 keyCode;
					UInt32 modifiers;
					GetEventParameter(inEvent, kEventParamKeyMacCharCodes, typeChar, NULL, sizeof (char), NULL, &macCharCode);
					GetEventParameter(inEvent, kEventParamKeyCode, typeUInt32, NULL, sizeof (UInt32), NULL, &keyCode);
					GetEventParameter(inEvent, kEventParamKeyModifiers, typeUInt32, NULL, sizeof (UInt32), NULL, &modifiers);

          VstKeyCode key;
          key.character = macCharCode;
          ((cBitmapFontEditable*)control)->onKeyDown(key);
          break;
				}
			}
			break;
		}
		case kEventClassMouse:
		{
			switch (eventKind)
			{
				case kEventMouseDown:
				{
					WindowRef window;
					GetEventParameter(inEvent, kEventParamWindowRef, typeWindowRef, NULL, sizeof(WindowRef), NULL, &window);
					HIPoint p;
					GetEventParameter(inEvent, kEventParamMouseLocation, typeHIPoint, NULL, sizeof(HIPoint), NULL, &p);
					Point point = { (short)p.y, (short)p.x };
					QDGlobalToLocalPoint(GetWindowPort(window), &point);
					CRect crect;
          control->getViewSize(crect);
          Rect rect;
          rect.top = crect.top;
          rect.left = crect.left;
          rect.right = crect.right;
          rect.bottom = crect.bottom;
					//TXNGetViewRect((cBitmap)textEdit->platformControl, &rect);
					if(PtInRect(point, &rect)) {
						EventRecord eventRecord;
						if(eventKind == kEventMouseDown && ConvertEventRefToEventRecord(inEvent, &eventRecord)) {
              // Mouse click received
            }
            else {
              VstKeyCode key;
              key.character = KEY_ESC;
              control->onKeyDown(key);
            }
            result = noErr;
					}
					break;
				}
			}
			break;
		}      
		case kEventClassWindow:
		{
			WindowRef window;
			if(GetEventParameter(inEvent, kEventParamDirectObject, typeWindowRef, NULL,
                           sizeof (WindowRef), NULL, &window) != noErr) {
				break;
      }
			switch(eventKind) {
				case kEventWindowDeactivated:
				{
					result = CallNextEventHandler(inHandlerCallRef, inEvent);
					ClearKeyboardFocus(window);
          
					// set up the correct drawing port for the window
					GrafPtr	savedPort;
					bool portChanged = QDSwapPort(GetWindowPort (window), &savedPort);
          
					// remember the current resource map ID
					short currentResID = CurResFile();
					short vstResFileID = control->pluginResID;
					// if it's different (and if it's valid), set the current resource map ID to our plugin's resource map
					if((vstResFileID != currentResID) && (vstResFileID > 0)) {
						UseResFile(vstResFileID);
          }
          
					VstKeyCode key;
          key.character = KEY_ESC;
          ((cBitmapFontEditable*)control)->onKeyDown(key);
          
					// revert the window port, if we changed it
					if(portChanged) {
						QDSwapPort(savedPort, NULL);
          }
          
					// revert the current resource map, if we changed it
					if((currentResID > 0) && (vstResFileID != currentResID) && (vstResFileID > 0)) {
						UseResFile(currentResID);
          }
          
					break;
				}
			}
			break;
		}
	}
	return result;
}
#endif


cBitmapFontEditable::cBitmapFontEditable(const CRect &size, CControlListener *listener, long tag,
                                         CBitmap *background, int spacing, int characters) :
cBitmapFont(size, listener, tag, background, spacing, characters) {
  setWantsFocus(true);
#ifdef MAC
  pluginResID = CurResFile();
#endif
  setMouseEnabled(true);
  setMouseableArea(size);
  memset(m_edit_buffer, 0x0, sizeof(char) * MAX_EDIT_CHARS);
  m_editing = false;
  m_edit_index = 0;
}

cBitmapFontEditable::~cBitmapFontEditable() {
}

void cBitmapFontEditable::draw(CDrawContext *pContext) {
  if(m_editing) {
    CColor textbg = { 196, 196, 196, 255 };
    pContext->setFillColor(textbg);
    pContext->setFrameColor(textbg);
    pContext->drawRect(size, kDrawFilledAndStroked);
  }
  cBitmapFont::draw(pContext);
}

void cBitmapFontEditable::mouse(CDrawContext *pContext, CPoint &where, long buttons) {
  takeFocus(pContext);
}

long cBitmapFontEditable::onKeyDown(VstKeyCode &keyCode) {
  if(!m_editing) {
    return 0;
  }
  if(m_edit_index >= MAX_EDIT_CHARS || keyCode.character == KEY_ESC ||
     keyCode.character == KEY_ENTER || keyCode.character == KEY_TAB ||
     keyCode.character == KEY_RETURN || keyCode.character == 0) {
    if(keyCode.character == KEY_ESC) {
      setText(m_old_buffer);
    }
    else {
      setText(m_edit_buffer);
    }
    m_editing = false;
    looseFocus();
    return 0;
  }
  else if(keyCode.character == KEY_DELETE && m_edit_index >= 0) {
    if(m_edit_index) {
      m_edit_buffer[--m_edit_index] = '\0';
    }
    else {
      m_edit_index = 0;
      m_edit_buffer[0] = '\0';
    }
  }
  else {
    m_edit_buffer[m_edit_index++] = (char)keyCode.character;
  }
    
  if(m_edit_index >= m_max_chars) {
    setText(m_edit_buffer + m_edit_index - m_max_chars);
  }
  else {
    setText(m_edit_buffer);
  }
  
  return keyCode.character;
}

void cBitmapFontEditable::takeFocus(CDrawContext *pContext) {
  if(!m_editing) {
    getText((char*)&m_old_buffer);
  }
  m_editing = true;
  
  if(m_edit_index) {
    m_edit_index = 0;
    memset(m_edit_buffer, 0x0, sizeof(char) * MAX_EDIT_CHARS);
  }
  setText(" ");
    
#if WINDOWS || MACX
	// calculate offset for CViewContainers
	CRect rect (size);
	CView* parent = getParentView ();
	CRect vSize;
	while (parent)
	{
		if (parent->notify (this, kMsgCheckIfViewContainer) == kMessageNotified)
		{
			parent->getViewSize (vSize);
			rect.offset (vSize.left, vSize.top);
		}
		parent = parent->getParentView ();
	}
	if (pContext)
		rect.offset (pContext->offset.h, pContext->offset.v);
#endif
  
#if WINDOWS
//	int wstyle = 0;
//	if (horiTxtAlign == kLeftText)
//		wstyle |= ES_LEFT;
//	else if (horiTxtAlign == kRightText)
//		wstyle |= ES_RIGHT;
//	else
//		wstyle |= ES_CENTER;
//  
//	wstyle |= WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL;
//	platformControl = (void*)CreateWindow (
//                                         "EDIT", text, wstyle,
//                                         rect.left, rect.top, rect.width ()/* + 1*/, rect.height ()/* + 1*/,
//                                         (HWND)getFrame ()->getSystemWindow (), NULL, GetInstance (), 0);
//  
//	// get/set the current font
//	LOGFONT logfont = {0};
//  
//	long fontH = gStandardFontSize [fontID];
//	if (fontH > rect.height () - 2)
//		fontH = rect.height () - 2;
//  
//	logfont.lfWeight = FW_NORMAL;
//	logfont.lfHeight = -fontH;
//	logfont.lfPitchAndFamily = VARIABLE_PITCH | FF_SWISS;
//	strcpy (logfont.lfFaceName, gStandardFontName[fontID]);
//  
//	logfont.lfClipPrecision	 = CLIP_STROKE_PRECIS;
//	logfont.lfOutPrecision	 = OUT_STRING_PRECIS;
//	logfont.lfQuality 	     = DEFAULT_QUALITY;
//	logfont.lfCharSet        = ANSI_CHARSET;
//  
//	platformFont = (HANDLE)CreateFontIndirect (&logfont);
//	platformFontColor = 0;
//  
	SetWindowLongPtr ((HWND)platformControl, GWLP_USERDATA, (LONG_PTR)this);
//	SendMessage ((HWND)platformControl, WM_SETFONT, (WPARAM)platformFont, true);
	SendMessage ((HWND)platformControl, EM_SETMARGINS, EC_LEFTMARGIN|EC_RIGHTMARGIN, MAKELONG (0, 0));
//	SendMessage ((HWND)platformControl, EM_SETSEL, 0, -1);
	SendMessage ((HWND)platformControl, EM_LIMITTEXT, 255, 0);
	SetFocus ((HWND)platformControl);

	oldWndProcEdit = (WINDOWSPROC)SetWindowLongPtr ((HWND)platformControl, GWLP_WNDPROC, (LONG_PTR)WindowProcEdit);
  
#elif MAC
	WindowRef window = (WindowRef)getFrame()->getSystemWindow();
  SetUserFocusWindow(window);
  AdvanceKeyboardFocus(window);
  EventTypeSpec eventTypes[] = {
    { kEventClassMouse, kEventMouseDown },
    { kEventClassWindow, kEventWindowDeactivated },
    { kEventClassKeyboard, kEventRawKeyDown },
    { kEventClassKeyboard, kEventRawKeyRepeat }
  };
  InstallWindowEventHandler(window, TextControlProc, GetEventTypeCount(eventTypes),
                            eventTypes, this, &gEventHandler);
#endif
  
  setDirty();
}

//------------------------------------------------------------------------
void cBitmapFontEditable::looseFocus(CDrawContext *pContext) { 
  // Call this yet to avoid recursive call
	endEdit();
	if(getFrame()->getFocusView() == this) {
		getFrame()->setFocusView(0);
  }
  
#if WINDOWS
//	char newText[255];
//	GetWindowText((HWND)platformControl, newText, 255);
//	strcpy (text, newText);
  
	DestroyWindow ((HWND)platformControl);
#elif MAC
	if(gEventHandler) {
		RemoveEventHandler(gEventHandler);
	}
  gEventHandler = 0;
#endif
  
  m_editing = false;
  setDirty(true);
  if(listener) {
    listener->valueChanged(pContext, this);
  }
  
  CControl::looseFocus(pContext);
}

