/*
 *  cSplashScreen.h
 *  KickMaker
 *
 *  Created by Nik Reiman on 31.03.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __cSplashScreen_H
#define __cSplashScreen_H

#ifndef __eventManager_H
#include "eventManager.h"
#endif

#ifndef __vstcontrols__
#include "vstcontrols.h"
#endif

class cSplashScreen : public CControl, public eventListener {
public:
  cSplashScreen(const CRect &size, CControlListener *listener, long tag, CBitmap *splash);
  ~cSplashScreen();

  virtual void draw(CDrawContext *pContext);
  virtual void handleEvent(void *data);
  virtual bool hitTest (const CPoint& where, const long buttons);
  virtual void mouse(CDrawContext *pContext, CPoint &where, long buttons=-1);
  virtual void setVisible(bool val = true);
protected:
  CBitmap *m_screen;
  CRect m_size;
  bool m_visible;
private:

};

#endif