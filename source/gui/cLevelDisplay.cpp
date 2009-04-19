/*
 *  cLevelDisplay.cpp
 *  KickMaker
 *
 *  Created by Nik Reiman on 18.03.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __cLevelDisplay_H
#include "cLevelDisplay.h"
#endif

cLevelDisplay::cLevelDisplay(const CRect &size, CControlListener *listener, long tag, CBitmap *pBackground) :
CControl(size, listener, tag, pBackground) {
  setTransparency(true);
}

cLevelDisplay::~cLevelDisplay() {
}

void cLevelDisplay::draw(CDrawContext *pContext) {
  int level = DEF_LIGHTEST - (int)(getValue() * (DEF_LIGHTEST - DEF_DARKEST));
  CColor dispcolor = {level, level, level, 255};
  pContext->setFillColor(dispcolor);
  pContext->setFrameColor(kBlackCColor);
  pContext->drawRect(m_size, kDrawFilledAndStroked);
  setDirty(false);
}

void cLevelDisplay::setValue(float val) {
  CControl::setValue(val);

  m_size.left = size.left;
  m_size.top = size.top;
  m_size.bottom = size.bottom;
  m_size.right = size.left + (int)(size.width() * val);
}