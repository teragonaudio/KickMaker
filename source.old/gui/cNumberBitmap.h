/*
 *  cNumberBitmap.h
 *  KickMaker
 *
 *  Created by Nik Reiman on 23.03.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __cNumberBitmap_H
#define __cNumberBitmap_H

#ifndef __cBitmapFont_H
#include "cBitmapFont.h"
#endif

#define DEF_LEFT 1
#define DEF_RIGHT 2

class cNumberBitmap : public cBitmapFont {
public:
  cNumberBitmap(const CRect &size, CControlListener *listener, long tag, CBitmap *background,
                int spacing, int characters = 12);
  ~cNumberBitmap();
  
  virtual void draw(CDrawContext *pContext);
  virtual void setBackground(bool val);
  virtual void setNumber(float number);
  virtual void setPrecision(int left, int right);
protected:
    bool m_draw_background;
    int m_left, m_right;
  char *m_number;
private:
};

#endif