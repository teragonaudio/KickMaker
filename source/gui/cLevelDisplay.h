/*
 *  cLevelDisplay.h
 *  KickMaker
 *
 *  Created by Nik Reiman on 18.03.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __cLevelDisplay_H
#define __cLevelDisplay_H

#ifndef __vstcontrols__
#include "vstcontrols.h"
#endif

#define DEF_LIGHTEST 120
#define DEF_DARKEST 50

class cLevelDisplay : public CControl {
public:
  cLevelDisplay(const CRect &size, CControlListener *listener, long tag, CBitmap *pBackground);
  ~cLevelDisplay();
  
  virtual void draw(CDrawContext *pContext);
  virtual void setValue(float val);
protected:
private:
    CRect m_size;
};

#endif