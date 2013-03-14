/*
 *  cSplashScreenVersion.h
 *  KickMaker
 *
 *  Created by Nik Reiman on 11.08.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __cSplashScreenVersion_H
#define __cSplashScreenVersion_H

#ifndef __CSplashScreen_H
#include "CSplashScreen.h"
#endif

#ifndef __defaults_H
#include "defaults.h"
#endif

#define DEF_VERSION_HEIGHT 15
#define MAX_VSTRING_SIZE 64

#ifdef WINDOWS
#define snprintf _snprintf
#endif

class cSplashScreenVersion : public CControl {
public:
  cSplashScreenVersion(const CRect &size, CControlListener *listener, long tag,
                       CBitmap *splash, CRect &wsize);
  ~cSplashScreenVersion();
  
  virtual void draw(CDrawContext *pContext);
  virtual bool hitTest(const CPoint &where, const long buttons = -1);
  virtual void mouse(CDrawContext *pContext, CPoint &where, long buttons = -1);
  virtual void setVisible(bool val = true);
protected:
  CTextLabel *m_version;
  CRect m_click_area;
  CRect m_splash_area;
  CBitmap *m_splash;
  bool m_visible;
private:
};

#endif