/*
 *  cTransparentLabel.h
 *  Convolver2
 *
 *  Created by Nik Reiman on 04.05.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __cTransparentLabel_H
#define __cTransparentLabel_H

#ifndef __eventManager_H
#include "eventManager.h"
#endif

#ifndef __vstcontrols__
#include "vstcontrols.h"
#endif

#include <stdio.h>

#define MAX_LABEL_SIZE 128

#if WINDOWS
#define snprintf _snprintf
#endif

class cTransparentLabel : public CParamDisplay, public eventListener {
public:
  cTransparentLabel(CRect &size, char *text = 0);
  ~cTransparentLabel();
  
  virtual void draw(CDrawContext *pContext);
  virtual void handleEvent(void *data = 0);
  virtual void setLabel(char *text);
  virtual void setLabel(float num);
  virtual void setLabel(int num);
protected:
    char m_label[MAX_LABEL_SIZE];
private:
};

#endif