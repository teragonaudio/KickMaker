/*
 *  cSplashScreenVersion.cpp
 *  KickMaker
 *
 *  Created by Nik Reiman on 11.08.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __cSplashScreenVersion_H
#include "cSplashScreenVersion.h"
#endif

cSplashScreenVersion::cSplashScreenVersion(const CRect &size, CControlListener *listener, long tag,
                                           CBitmap *splash, CRect &wsize) :
CControl(wsize, listener, tag) {
  m_visible = false;
  
  CRect tsize = wsize;
  char vstring[MAX_VSTRING_SIZE];
  tsize.top = wsize.bottom - DEF_VERSION_HEIGHT;
  m_version = new CTextLabel(tsize);
  m_version->setFontColor(kWhiteCColor);
  m_version->setFrameColor(kBlackCColor);
  m_version->setBackColor(kBlackCColor);
  
  // This class expects the following preprocessor definitions to be defined in defaults.h
  // DEF_PRODUCT - product name
  // MAJ_VERSION - major version
  // MIN_VERSION - minor version
  // REL_BRANCH - can be either 'r' (release), 'b' (beta), or 'a' (alpha)
  switch(REL_BRANCH) {
    case 'a':
      snprintf(vstring, MAX_VSTRING_SIZE, "%s-v%d.0a%d - alpha", DEF_PRODUCT, MAJ_VERSION, MIN_VERSION);
      break;
    case 'b':
      snprintf(vstring, MAX_VSTRING_SIZE, "%s-v%d.0b%d - beta", DEF_PRODUCT, MAJ_VERSION, MIN_VERSION);
      break;
    case 'r':
    default:
      snprintf(vstring, MAX_VSTRING_SIZE, "%s-v%d.%d - Copyright 2006 Teragon Audio", DEF_PRODUCT, MAJ_VERSION, MIN_VERSION);
      break;
  }
  m_version->setText(vstring);
  
  m_click_area = size;
  
  m_splash = splash;
  if(m_splash) {
    m_splash_area((wsize.getWidth() / 2) - (m_splash->getWidth() / 2),
                  (wsize.getHeight() / 2) - (m_splash->getHeight() / 2),
                  (wsize.getWidth() / 2) + (m_splash->getWidth() / 2),
                  (wsize.getHeight() / 2) + (m_splash->getHeight() / 2));
  }
}

cSplashScreenVersion::~cSplashScreenVersion() {
  m_splash->forget();
  delete m_version;
}

void cSplashScreenVersion::draw(CDrawContext *pContext) {
  if(m_visible) {
    if(m_splash) {
      m_splash->draw(pContext, m_splash_area);
    }
    m_version->draw(pContext);
  }
  
  setDirty(false);
}

bool cSplashScreenVersion::hitTest(const CPoint &where, const long buttons) {
  if(m_visible) {
    return true;
  }
  if(where.isInside(m_click_area)) {
    return true;
  }
  else {
    return false;
  }
}

void cSplashScreenVersion::mouse(CDrawContext *pContext, CPoint &where, long buttons) {
  setVisible(!m_visible);
  CControl::mouse(pContext, where, buttons);
}

void cSplashScreenVersion::setVisible(bool val) {
  m_visible = val;
  setDirty();
}