/*
 *  cLevelDisplayText.h
 *  KickMaker
 *
 *  Created by Nik Reiman on 10.08.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __cLevelDisplayText_H
#define __cLevelDisplayText_H

#ifndef __cLevelDisplay_H
#include "cLevelDisplay.h"
#endif

class cLevelDisplayText : public cLevelDisplay {
public:
  cLevelDisplayText(const CRect &size, CControlListener *listener, long tag, CBitmap *pBackground);
  ~cLevelDisplayText();
  
protected:
private:
};

#endif