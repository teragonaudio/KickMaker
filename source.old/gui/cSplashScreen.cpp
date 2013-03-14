/*
 *  cSplashScreen.cpp
 *  KickMaker
 *
 *  Created by Nik Reiman on 31.03.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __cSplashScreen_H
#include "cSplashScreen.h"
#endif

cSplashScreen::cSplashScreen(const CRect &size, CControlListener *listener, long tag, CBitmap *splash) :
CControl(size, listener, tag, 0) {
  m_screen = splash;
  m_visible = false;
  m_size = size;
}

cSplashScreen::~cSplashScreen() {
}

void cSplashScreen::draw(CDrawContext *pContext) {
  if(m_visible) {
    m_screen->draw(pContext, m_size);
  }

  setDirty(false);
}

void cSplashScreen::handleEvent(void *data) {
  if(data) {
    m_visible = true;
  }
  else {
    m_visible = false;
  }
  setDirty();
}

bool cSplashScreen::hitTest(const CPoint& where, const long buttons) {
  if(m_visible) {
    return CView::hitTest(where, buttons);
  }
  else {
    return false;
  }
}

void cSplashScreen::mouse(CDrawContext *pContext, CPoint &where, long buttons) {
  if(m_visible) {
    setVisible(false);
  }
  if(listener) {
    listener->valueChanged(pContext, this);
  }
}

void cSplashScreen::setVisible(bool val) {
  m_visible = val;
  setDirty();
}