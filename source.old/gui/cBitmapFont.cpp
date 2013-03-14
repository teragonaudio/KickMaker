/*
 *  cBitmapFont.cpp
 *  KickMaker
 *
 *  Created by Nik Reiman on 22.03.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __cBitmapFont_H
#include "cBitmapFont.h"
#endif

// Takes in a bitmap filmstrip in the following format:
// 0-9 A-Z a-z . *
cBitmapFont::cBitmapFont(const CRect &size, CControlListener *listener, long tag,
                         CBitmap *background, int spacing, int characters) :
CControl(size, listener, tag, background) {
  setTransparency(true);
  m_num_chars = 0;
  m_is_hidden = false;
  m_max_chars = (int)((float)size.width() / (float)(background->getWidth() + spacing));
  m_font_height = (int)((float)background->getHeight() / (float)characters);
  memset(m_orig_text, 0x0, sizeof(char) * MAX_BUFFER_CHARS);
  m_text = NULL;
  m_char_index = NULL;
  m_sizes = NULL;

  if(m_max_chars > 0) {
    m_text = new char[m_max_chars];
    memset(m_text, 0x0, sizeof(char) * m_max_chars);
    m_char_index = new int[m_max_chars];
    m_sizes = new CRect[m_max_chars];
    
    CRect tmpsize(size.left, size.top, size.left + background->getWidth(), size.top + m_font_height);    
    for(int i = 0; i < m_max_chars; ++i) {
      m_char_index[i] = 0;
      m_sizes[i] = tmpsize;
      tmpsize.left = tmpsize.right + spacing;
      tmpsize.right = tmpsize.left + background->getWidth();
    }
  }
}

cBitmapFont::~cBitmapFont() {
  if(m_text) {
    delete [] m_text;
  }
  if(m_char_index) {
    delete [] m_char_index;
  }
  if(m_sizes) {
    delete [] m_sizes;
  }
}

void cBitmapFont::blank() {
  for(int i = 0; i < m_max_chars; ++i) {
    m_char_index[i] = 0;
  }
  setDirty(true);
}

void cBitmapFont::draw(CDrawContext *pContext) {
  if(!m_is_hidden) {
    CPoint where(0, 0);
    for(int i = 0; i < m_num_chars; ++i) {
      where.v = m_font_height * m_char_index[i];
      pBackground->drawTransparent(pContext, m_sizes[i], where);
    }
  }
  setDirty(false);
}

bool cBitmapFont::getHidden() const {
  return m_is_hidden;
}

void cBitmapFont::getText(char *text) const {
  strcpy(text, (const char*)m_orig_text);
}

void cBitmapFont::hide(bool val) {
  m_is_hidden = val;
}

void cBitmapFont::setText(const char *text) {
  unsigned int i;
  strncpy(m_orig_text, text, MAX_BUFFER_CHARS);
  
  for(i = 0; i < m_max_chars && i < strlen(text); ++i) {
    if(text[i] == 32) { // Space character
      m_char_index[i] = 0;
    }
    else if(text[i] >= 48 && text[i] <= 57) { // Numbers
      m_char_index[i] = (int)text[i] - 48 + 1;
    }
    else if(text[i] >= 65 && text[i] <= 90) { // Capital letters
      m_char_index[i] = (int)text[i] - 65 + 1 + 10;
    }
    else if(text[i] >= 97 && text[i] <= 122) { // Lowercase letters
      m_char_index[i] = (int)text[i] - 97 + 1 + 10 + 26;
    }
    else if(text[i] == 46) { // Period
      m_char_index[i] = 1 + 10 + 26 + 26;
    }
    else { // Unknown character
      m_char_index[i] = 1 + 10 + 26 + 26 + 1;
    }

    m_text[i] = text[i];
  }
  if(i) {
    m_text[i] = '\0';
  }
  
  m_num_chars = i;
  setDirty(true);
}