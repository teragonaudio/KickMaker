/*
 *  cTransparentLabel.cpp
 *  Convolver2
 *
 *  Created by Nik Reiman on 04.05.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __cTransparentLabel_H
#include "cTransparentLabel.h"
#endif

cTransparentLabel::cTransparentLabel(CRect &size, char *text) : CParamDisplay(size) {
  setBackColor(kTransparentCColor);
  setFrameColor(kTransparentCColor);
	setFont(kNormalFontSmall);
	setFontColor(kBlackCColor);
  
  memset(m_label, 0x0, sizeof(char) * MAX_LABEL_SIZE);
  setLabel(text);
}

cTransparentLabel::~cTransparentLabel() {
}

void cTransparentLabel::draw(CDrawContext *pContext) {
  pContext->setFont(kNormalFontSmall);
  pContext->setFontColor(kBlackCColor);
  pContext->drawString(m_label, size, false, kLeftText);
  setDirty(false);
}

void cTransparentLabel::handleEvent(void *data) {
  // By default, clear out the text if an event is received
  setLabel((char*)" ");
}

void cTransparentLabel::setLabel(char *text) {
  if(text) {
    strncpy(m_label, text, MAX_LABEL_SIZE);
  }
  setDirty(true);
}

void cTransparentLabel::setLabel(float num) {
  char buf[MAX_LABEL_SIZE];
  snprintf(buf, MAX_LABEL_SIZE, "%0.2f", num);
  setLabel(buf);
}

void cTransparentLabel::setLabel(int num) {
  char buf[MAX_LABEL_SIZE];
  snprintf(buf, MAX_LABEL_SIZE, "%d", num);
  setLabel(buf);
}