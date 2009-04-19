/*
 *  cBitmapFont.h
 *  KickMaker
 *
 *  Created by Nik Reiman on 22.03.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __cBitmapFont_H
#define __cBitmapFont_H

#ifndef __vstcontrols__
#include "vstcontrols.h"
#endif

#ifndef __vstkeycode__
#include "vstkeycode.h"
#endif

#define MAX_BUFFER_CHARS 64
// Number of characters expected in filmstrip
#define NUM_CHARS 64

class cBitmapFont : public CControl {
public:
  cBitmapFont(const CRect &size, CControlListener *listener, long tag, CBitmap *background,
              int spacing, int characters);
  ~cBitmapFont();
  
  virtual void blank();
  virtual bool getHidden() const;
  virtual void getText(char *text) const;
  virtual void hide(bool val = true);
  virtual void draw(CDrawContext *pContext);
  virtual void setText(const char *text);
protected:
    char m_orig_text[MAX_BUFFER_CHARS];
  int *m_char_index;
  char *m_text;
  CRect *m_sizes;
  bool m_is_hidden;
  int m_max_chars;
  int m_num_chars;
  int m_font_height;
private:
};

#endif