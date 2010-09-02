/*
 *  vstLoaderEditor.cpp - pluginCore
 *
 *  Created by Nik Reiman on 07.07.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 *  This source code may NOT be redistributed without express permission of Teragon Audio.  It may be used
 *  in free or commercial software works, but unauthorized duplication or resale in whole or part is
 *  strictly prohibited.
 */

#if USE_PC_VST
#if USE_PC_HOST

#ifndef __vstLoader_H
#include "vstLoader.h"
#endif

#if WINDOWS
struct _DLGTEMPLATE : DLGTEMPLATE {
	WORD ext[3];
	_DLGTEMPLATE() { memset(this, 0, sizeof(*this)); };
};

static AEffect* _EFFECT = 0;
#endif

#if MAC
MenuRef _WINDOW_MENU;
#if USE_PC_MIDI
#define REF_MIDI_MENU 1000
MenuRef _MIDI_MENU;
std::vector<tMidiPort> _MIDI_PORTS;
#endif

pascal void idleTimerProc(EventLoopTimerRef inTimer, void *inUserData) {
	AEffect* effect = (AEffect*)inUserData;
	effect->dispatcher(effect, effEditIdle, 0, 0, 0, 0);
}

void QuitEditor(WindowRef window) {
  HideWindow(window);
}

pascal OSStatus windowHandler(EventHandlerCallRef inHandlerCallRef, EventRef inEvent, void *inUserData) {
	OSStatus result = eventNotHandledErr;
	WindowRef window = (WindowRef)inUserData;
	UInt32 eventClass = GetEventClass(inEvent);
	UInt32 eventKind = GetEventKind(inEvent);
  switch(eventClass) {
    case kEventClassMenu:
      switch(eventKind) {
        case kEventMenuClosed:
#if USE_PC_MIDI
          // Currently only the USE_PC_MIDI feature requires menu handling
          int menu = MenuChoice() >> 16;
          int item = MenuChoice() << 16 >> 16;
          CharParameter checked;
          switch(menu) {
            case REF_MIDI_MENU:
              if(item == 1) {
                break;
              }
              else if(item == 2) {
                break;
              }
              
              GetItemMark(_MIDI_MENU, item, &checked);
              if(!checked) {
                SetItemMark(_MIDI_MENU, item, checkMark);
              }
              else {
                SetItemMark(_MIDI_MENU, item, 0);
              }
              break;
						default:
              break;
          }
#endif
          break;
        case kEventMenuEnableItems:
#if USE_PC_MIDI
          EnableAllMenuItems(_MIDI_MENU);
#endif
					EnableAllMenuItems(_WINDOW_MENU);
          result = noErr;
          break;
        default:
          break;
      }
      break;
    case kEventClassMouse:
      switch(eventKind) {
        case kEventMouseDown:
          break;
        default:
          break;
      }
      break;
    case kEventClassKeyboard:
      char key;
      UInt32 modifiers;
      OSStatus result = GetEventParameter(inEvent, kEventParamKeyMacCharCodes, typeChar,
                                          NULL, sizeof(char), NULL, &key);
      result = GetEventParameter(inEvent, kEventParamKeyModifiers, typeUInt32,
                                 NULL, sizeof(UInt32), NULL, &modifiers);
      // Open-apple key
      if(modifiers == 256) {
        // Quit hooks
        if(key == 'q' || key == 'Q' || key == 'w' || key == 'W') {
          QuitAppModalLoopForWindow(window);
        }
      }
      
      //effect->dispatcher(effect, effKey, 0, 0, window, 0);
      break;
		case kEventClassWindow:
			switch(eventKind) {
        case kEventWindowClose:
          QuitAppModalLoopForWindow(window);
					break;
        case kEventWindowActivated:
					::CallNextEventHandler(inHandlerCallRef, inEvent);
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
  
  return result;
}
#endif

#if WINDOWS
INT_PTR CALLBACK EditorProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch(msg)	{
	  case WM_INITDIALOG:
		{
#ifdef DEF_PRODUCT
      SetWindowText(hwnd, DEF_PRODUCT);
#else
      SetWindowText(hwnd, "VST Editor");
#endif
      SetTimer(hwnd, 1, 20, 0);

			if(_EFFECT) {
        debug(LOG_INFO, "Sending dispatcher call to open editor");
        _EFFECT->dispatcher(_EFFECT, effEditOpen, 0, 0, hwnd, 0);

				ERect* eRect = 0;
				_EFFECT->dispatcher(_EFFECT, effEditGetRect, 0, 0, &eRect, 0);
				if(eRect) {
					int width = eRect->right - eRect->left;
					int height = eRect->bottom - eRect->top;
          if(width < 100) {
						width = 100;
          }
          if(height < 100) {
						height = 100;
          }

					RECT wRect;
					SetRect(&wRect, 0, 0, width, height);
					AdjustWindowRectEx(&wRect, GetWindowLong(hwnd, GWL_STYLE), FALSE,
                             GetWindowLong(hwnd, GWL_EXSTYLE));
					width = wRect.right - wRect.left;
					height = wRect.bottom - wRect.top;

					SetWindowPos(hwnd, HWND_TOP, 0, 0, width, height, SWP_NOMOVE);
				}
			}
		}
		break;

	case WM_TIMER:
    if(_EFFECT) {
			_EFFECT->dispatcher(_EFFECT, effEditIdle, 0, 0, 0, 0);
    }
		break;

	case WM_CLOSE:
      {
			KillTimer(hwnd, 1);

      debug(LOG_INFO, "Closing editor");
      if(_EFFECT) {
				_EFFECT->dispatcher(_EFFECT, effEditClose, 0, 0, 0, 0);
      }
			EndDialog(hwnd, IDOK);
		}
		break;
	}

	return 0;
}
#endif

void *openEditor(void *e) {
  AEffect *effect = reinterpret_cast<AEffect*>(e);
	if(effect && (effect->flags & effFlagsHasEditor) == 0) {
		debug(LOG_ERROR, "Plugin has no editor");
    return NULL;
	}
  
#if WINDOWS
  _EFFECT = (AEffect*)e;
	_DLGTEMPLATE t;	
	t.style = WS_POPUPWINDOW | WS_DLGFRAME | DS_MODALFRAME | DS_CENTER;
	t.cx = 100;
	t.cy = 100;
	DialogBoxIndirectParam(GetModuleHandle(0), &t, 0, (DLGPROC)EditorProc, (LPARAM)e);
  _EFFECT = 0;
#endif
#if MAC
  WindowRef window;
	Rect mRect = {0, 0, 300, 300};
	OSStatus err = CreateNewWindow(kUtilityWindowClass,
                                 kWindowCloseBoxAttribute | kWindowCompositingAttribute |
                                 kWindowAsyncDragAttribute | kWindowStandardHandlerAttribute |
                                 kWindowCollapseBoxAttribute,
                                 &mRect, &window);
	if(err != noErr) {
		return NULL;
	}
	static EventTypeSpec eventTypes[] = {
    { kEventClassMenu, kEventMenuEnableItems },
    { kEventClassMenu, kEventMenuClosed },
    { kEventClassWindow, kEventWindowActivated },
		{ kEventClassWindow, kEventWindowClose },
    { kEventClassMouse, kEventMouseDown },
    { kEventClassMouse, kEventMouseUp },
    { kEventClassMouse, kEventMouseMoved },
    { kEventClassMouse, kEventMouseDragged },
    { kEventClassKeyboard, kEventRawKeyDown }
//    { kEventClassKeyboard, kEventHotKeyPressed },
	};
  CFStringRef wtitle;
  
#ifdef DEF_PRODUCT
  wtitle = CFStringCreateWithCStringNoCopy(NULL, DEF_PRODUCT, NULL, NULL);
#else
  wtitle = CFSTR("Plugin Editor");
#endif
  
  EventHandlerRef eref;
  SetWindowTitleWithCFString(window, wtitle);
  err = InstallWindowEventHandler(window, windowHandler, GetEventTypeCount(eventTypes),
                                  eventTypes, window, &eref);
  if(err != noErr) {
    return NULL;
  }
  
#if USE_PC_MIDI
  // Insert midi devices menu
  CreateNewMenu(REF_MIDI_MENU, 0, &_MIDI_MENU);
  SetMenuTitleWithCFString(_MIDI_MENU, CFSTR("MIDI Input"));
  int menunum = 0;
  InsertMenuItemTextWithCFString(_MIDI_MENU, CFSTR("Rescan Devices"),
                                 menunum++, kMenuItemAttrIconDisabled, 0);
  InsertMenuItemTextWithCFString(_MIDI_MENU, NULL, menunum++, kMenuItemAttrSeparator, 0);
  
  scanMidi();
  for(int i = 0; i < _MIDI_PORTS.size(); ++i) {
    char menutext[MAX_DEV_NAME];
    snprintf(menutext, MAX_DEV_NAME, "%s, Port %d",
             CFStringGetCStringPtr((CFStringRef)_MIDI_PORTS.at(i).devicename, kCFStringEncodingMacRoman),
             _MIDI_PORTS.at(i).portnumber);
    InsertMenuItemTextWithCFString(_MIDI_MENU, CFStringCreateWithCString(kCFAllocatorDefault,
                                                                         menutext,
                                                                         kCFStringEncodingMacRoman),
                                   menunum++, kMenuItemAttrIconDisabled, i);
  }
  InsertMenu(_MIDI_MENU, 0);
#endif  
  
  // TODO: Insert audio I/O menu
  
  // Insert standard window menu
  CreateStandardWindowMenu(0, &_WINDOW_MENU);
	InsertMenu(_WINDOW_MENU, 1);
  
  DrawMenuBar();
  
	ERect* eRect = 0;
	effect->dispatcher(effect, effEditGetRect, 0, 0, &eRect, 0);
	if(eRect)	{
		int width = eRect->right - eRect->left;
		int height = eRect->bottom - eRect->top;
		Rect bounds;
		GetWindowBounds(window, kWindowContentRgn, &bounds);
		bounds.right = bounds.left + width;
		bounds.bottom = bounds.top + height;
		SetWindowBounds(window, kWindowContentRgn, &bounds); 
	}
	RepositionWindow(window, NULL, kWindowCenterOnMainScreen);
  debug(LOG_INFO, "Sending dispatcher call to open editor");
  effect->dispatcher(effect, effEditOpen, 0, 0, window, 0);
  
	EventLoopTimerRef idleEventLoopTimer;
	InstallEventLoopTimer(GetCurrentEventLoop(), 0.1, 0.1, idleTimerProc, effect, &idleEventLoopTimer);
  InvokeEventLoopTimerUPP(idleEventLoopTimer, effect, idleTimerProc);
  
  SelectWindow(window);
  ActivateWindow(window, true);
	ShowWindow(window);
  RunAppModalLoopForWindow(window);
  
  // Execution will resume here once the runloop is terminated
  debug(LOG_INFO, "Closing editor");
  RemoveEventLoopTimer(idleEventLoopTimer);
  effect->dispatcher(effect, effEditClose, 0, 0, 0, 0);
	err = ReleaseWindow(window);
#endif
  
 	return NULL;
}

#if USE_PC_MIDI && MAC
void scanMidi() {
  _MIDI_PORTS.clear();
  
  for(int i = 0; i < MIDIGetNumberOfDevices(); ++i) {
    MIDIDeviceRef dev = MIDIGetDevice(i);
    CFPropertyListRef props;
    MIDIObjectGetProperties(dev, &props, true);
    const void *name;
    const void *offline;
    bool result;
    
    result = CFDictionaryGetValueIfPresent((CFDictionaryRef)props, CFSTR("offline"), &offline);
    if(!result) {
      continue;
    }
    else {
      int realval;
      CFNumberGetValue((CFNumberRef)offline, kCFNumberIntType, &realval);
      if(realval) {
        continue;
      }
    }
    result = CFDictionaryGetValueIfPresent((CFDictionaryRef)props, CFSTR("name"), &name);
    if(!result) {
      continue;
    }
    
    for(int j = 0; j < MIDIDeviceGetNumberOfEntities(dev); ++j) {
      MIDIEntityRef ent = MIDIDeviceGetEntity(dev, j);
      if(MIDIEntityGetNumberOfSources(ent)) {
        tMidiPort p;
        strncpy(p.devicename, CFStringGetCStringPtr((CFStringRef)name, kCFStringEncodingMacRoman),
                MAX_DEV_NAME);
        p.entity = ent;
        p.portnumber = j;
      }
    }
  }
}
#endif

#endif
#endif