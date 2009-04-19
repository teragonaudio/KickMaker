/*
 *  cSmartKnob.h
 *  KickMaker
 *
 *  Created by Nik Reiman on 23.03.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __cSmartKnob_H
#define __cSmartKnob_H

#ifndef __cNumberBitmap_H
#include "cNumberBitmap.h"
#endif

#ifndef __eventManager_H
#include "eventManager.h"
#endif

#ifndef __vstcontrols__
#include "vstcontrols.h"
#endif

class cSmartKnob : public CControl, public eventListener {
public:
  cSmartKnob(const CRect &size, CControlListener *listener, long tag, long subPixmaps,
             CCoord heightOfOneImage, CBitmap *background, CBitmap *fontmap, CPoint &offset, CFrame *frame);
  ~cSmartKnob();
  
  virtual void draw(CDrawContext *pContext);
  virtual void handleEvent(void *data);
  virtual void mouse (CDrawContext *pContext, CPoint &where, long button);
  virtual void setDirty(const bool val = true);
  virtual void setNumber(float number);
  virtual void setPrecision(int left, int right);
  virtual void setTag(long tag);
  virtual void setValue(float val);
protected:
    cNumberBitmap *m_number_display;
  CAnimKnob *m_anim_knob;
  int m_display_height;
private:
};

#endif