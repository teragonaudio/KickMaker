/*
 *  cBitmapFontEditable.h
 *  KickMaker
 *
 *  Created by Nik Reiman on 06.04.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __cBitmapFontEditable_H
#define __cBitmapFontEditable_H

#ifndef __cBitmapFont_H
#include "cBitmapFont.h"
#endif

#include <vstkeycode.h>

#define KEY_DELETE 8
#define KEY_ENTER 3
#define KEY_RETURN 13
#define KEY_ESC 27
#define KEY_TAB 9
#define MAX_EDIT_CHARS 128

class cBitmapFontEditable : public cBitmapFont {
public:
  cBitmapFontEditable(const CRect &size, CControlListener *listener, long tag, CBitmap *background,
                      int spacing, int characters);
  ~cBitmapFontEditable();
  
  virtual void draw(CDrawContext *pContext);
  virtual long onKeyDown(VstKeyCode &keyCode);
  virtual void mouse(CDrawContext *pContext, CPoint &where, long buttons = -1);
  virtual void takeFocus(CDrawContext *pContext);
  virtual void looseFocus(CDrawContext *pContext = 0);

  	void *platformFontColor;
	void *platformControl;
	bool bWasReturnPressed;

#if MAC
  short pluginResID;
#endif
protected:

    char m_edit_buffer[MAX_EDIT_CHARS];
  char m_old_buffer[MAX_EDIT_CHARS];
    bool m_editing;
    int m_edit_index;
private:
};

#endif