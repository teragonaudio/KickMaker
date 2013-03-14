/*
 *  cNumberBitmap.cpp
 *  KickMaker
 *
 *  Created by Nik Reiman on 23.03.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __cNumberBitmap_H
#include "cNumberBitmap.h"
#endif

cNumberBitmap::cNumberBitmap(const CRect &size, CControlListener *listener, long tag,
                             CBitmap *background, int spacing, int characters) :
cBitmapFont(size, listener, tag, background, spacing, characters) {
  setPrecision(DEF_LEFT, DEF_RIGHT);
  m_number = new char[m_max_chars];
  hide(true);
  m_draw_background = false;
}

cNumberBitmap::~cNumberBitmap() {
  delete [] m_number;
}

void cNumberBitmap::draw(CDrawContext *pContext) {
  if(!getHidden()) {
    if(m_draw_background) {
      CColor bg = { 255, 255, 255, 170 };
      pContext->setFillColor(bg);
      pContext->setFrameColor(kBlackCColor);
      pContext->drawRect(size, kDrawFilled);
    }
    cBitmapFont::draw(pContext);
  }
  setDirty(false);
}

void cNumberBitmap::setBackground(bool val) {
  m_draw_background = val;
}

void cNumberBitmap::setNumber(float number) {
  memset(m_number, 0x0, sizeof(char) * m_max_chars);
  int left = (int)number;
  float right = (float)(number - (int)number);
  
  // First draw text to the left (integer portion)
  int i;
  for(i = m_left - 1; i >= 0; --i) {
    if(left > 0) {
      m_number[i] = (char)((left % 10) + 48);
      left /= 10;
    }
    else {
      m_number[i] = ' ';
    }
  }
  
  if(!(m_left + 1 >= m_num_chars)) {
    // Decimal point
    m_number[m_left] = '.';
  }
  else {
    setText(m_number);  
    setDirty(true);
    return;
  }
  
  for(i = m_left + 1; i < m_num_chars; ++i) {
    right *= 10.0;
    int digit = (int)right % 10;
    if(digit >= 0 && digit <= 9) {
      m_number[i] = (char)(digit + 48);
    }
    else {
      m_number[i] = '0';
    }
  }
  
  setText(m_number);
  hide(false);
  setDirty(true);
}

void cNumberBitmap::setPrecision(int left, int right) {
  // Left + decimal point is too big, so just use left side
  if(left + 1 > m_max_chars) {
    m_left = m_max_chars;
    m_right = 0;
    m_num_chars = m_left;
  }
  // Left + decimal point + right will fit, so chop the right and adjust accordingly 
  else if(left + right + 1 > m_max_chars) {
    m_left = left;
    m_right = m_max_chars - left - 1;
    m_num_chars = m_left + m_right + 1;
  }
  // Full left and right
  else {
    m_left = left;
    m_right = right;
    m_num_chars = m_left + m_right + 1;
  }
}