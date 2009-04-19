/*
 *  cADSRDisplay.h
 *  KickMaker
 *
 *  Created by Nik Reiman on 16.02.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __cADSRDisplay_H
#define __cADSRDisplay_H

#ifndef __defaults_H
#include "defaults.h"
#endif

#ifndef __vstgui__
#include "vstgui.h"
#endif

#include <math.h>

// Number of pixels away from a point we'll recognize as a click
#define DEF_MOUSE_TOLERANCE 10

class cADSRDisplay : public CControl {
public:
  cADSRDisplay(const CRect &size, CControlListener *listener, long tag, CBitmap *pBackground);
  ~cADSRDisplay();
  
  virtual void draw(CDrawContext *pContext);
  virtual void 	mouse (CDrawContext *pContext, CPoint &where, long buttons=-1);
  
  int distance(int x1, int y1, int x2, int y2) const;
  void setAttackCoords(float amount, float amp);
  void setDecayCoords(float amount, float amp);
  void setSustainCoords(float amount, float amp);
  void setReleaseCoords(float amount, float amp);
protected:
private:
    CDragContainer *dc;
  int m_attack_x, m_attack_y;
  int m_decay_x, m_decay_y;
  int m_sustain_x, m_sustain_y;
  int m_release_x, m_release_y;
  float m_attack_amp, m_decay_amp, m_sustain_amp;
};

#endif