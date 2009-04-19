/*
 *  cLevelDisplayBitmap.h
 *  KickMaker
 *
 *  Created by Nik Reiman on 30.03.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __cLevelDisplayBitmap_H
#define __cLevelDisplayBitmap_H

#ifndef __cNumberBitmap_H
#include "cNumberBitmap.h"
#endif

#ifndef __cLevelDisplay_H
#include "cLevelDisplay.h"
#endif

#include <vector>
#include <string>

using namespace std;

class cLevelDisplayBitmap : public cLevelDisplay {
public:
  cLevelDisplayBitmap(const CRect &size, CControlListener *listener, long tag,
                      CBitmap *pBackground, CBitmap *fontmap,
                      int display_offset_x = 0, int display_offset_y = 0);
  ~cLevelDisplayBitmap();
  
  virtual void draw(CDrawContext *pContext);
  virtual void setDisplayType(bool is_numerical_only = true);
  virtual void setNumber(float value);
  virtual void setPrecision(int left, int right);
  virtual void setRange(float min, float max);
  virtual void setValue(float value);
  virtual void setString(char *text, float value);
  
  // Dictianory-related functions
  virtual void dictClear();
  virtual void dictAddEntry(string s);
  virtual void dictAddEntry(char *s);
  virtual string dictGetEntry(int index);
  
protected:
  vector<string> mDictionary;
  cNumberBitmap *m_display;
  bool mDisplayType; // True for numbers only, false for A-Z (uses currently set dictionary)
  float m_min;
  float m_max;
private:
};

#endif