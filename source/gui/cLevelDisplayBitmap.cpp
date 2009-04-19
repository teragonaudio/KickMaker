/*
 *  cLevelDisplayBitmap.cpp
 *  KickMaker
 *
 *  Created by Nik Reiman on 30.03.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __cLevelDisplayBitmap_H
#include "cLevelDisplayBitmap.h"
#endif

const int gFontmapCharCount = 10 + 26 + 26 + 2;

cLevelDisplayBitmap::cLevelDisplayBitmap(const CRect &size, CControlListener *listener, long tag,
                                         CBitmap *pBackground, CBitmap *fontmap,
                                         int display_offset_x, int display_offset_y) :
cLevelDisplay(size, listener, tag, pBackground) {
  CRect num_size(size.left + display_offset_x, size.top + display_offset_y, size.right - display_offset_x,
                 size.top + display_offset_y + (fontmap->getHeight() / gFontmapCharCount)); // Should divide evenly..
  m_display = new cNumberBitmap(num_size, listener, tag, fontmap, 0, gFontmapCharCount);
  m_display->hide(false);
  m_display->setPrecision(3, 0);
  m_min = 0.0;
  m_max = 1.0;
  mDisplayType = true;
}

cLevelDisplayBitmap::~cLevelDisplayBitmap() {
  mDictionary.clear();
}

void cLevelDisplayBitmap::draw(CDrawContext *pContext) {
  cLevelDisplay::draw(pContext);
  m_display->draw(pContext);
}

void cLevelDisplayBitmap::setDisplayType(bool is_numerical_only)
{
  mDisplayType = is_numerical_only;
}

void cLevelDisplayBitmap::setNumber(float value) {
  m_display->setNumber(value);
}

void cLevelDisplayBitmap::setPrecision(int left, int right) {
  m_display->setPrecision(left, right);
}

void cLevelDisplayBitmap::setRange(float min, float max) {
  m_min = min;
  m_max = max;
}

void cLevelDisplayBitmap::setValue(float value) {
  if(mDisplayType)
  {
    m_display->setNumber(value * 100);
  }
  else
  {
    // Need to scale {0.0, 1.0} to the range {0, size - 1}
    int index = (int)(value * (float)(mDictionary.size() - 1));
    if(mDictionary.size() > 0 && index >= 0 && index < mDictionary.size())
    {
      string s = mDictionary.at(index);
      m_display->setText(s.c_str());
    }
  }
  cLevelDisplay::setValue(value);
}

void cLevelDisplayBitmap::setString(char *text, float value) {
  m_display->setText(text);
  cLevelDisplay::setValue(value);
}

// Dictionary-related stuff
void cLevelDisplayBitmap::dictClear()
{
  mDictionary.clear();
}

void cLevelDisplayBitmap::dictAddEntry(string s)
{
  mDictionary.push_back(s);
}

void cLevelDisplayBitmap::dictAddEntry(char *s)
{
  // TODO: This, heh
}

string cLevelDisplayBitmap::dictGetEntry(int index)
{
  if(!mDictionary.size() || index < 0 || index >= mDictionary.size())
  {
    return NULL;
  }
  else
  {
    return mDictionary.at(index);
  }
}