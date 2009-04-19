/*
 *  cSmartKnob.cpp
 *  KickMaker
 *
 *  Created by Nik Reiman on 23.03.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __cSmartKnob_H
#include "cSmartKnob.h"
#endif

cSmartKnob::cSmartKnob(const CRect &size, CControlListener *listener, long tag, long subPixmaps,
                       CCoord heightOfOneImage, CBitmap *background, CBitmap *fontmap, CPoint &offset,
                       CFrame *frame) :
CControl(size, listener, -1, 0),
eventListener() {
  CRect tmpsize(size.left, size.top, size.right, size.top + (background->getHeight() / subPixmaps));
  m_anim_knob = new CAnimKnob(tmpsize, listener, tag, subPixmaps, heightOfOneImage, background, offset);
  frame->addView(m_anim_knob);
  
  m_display_height = heightOfOneImage;
  tmpsize(size.left, size.bottom - (fontmap->getHeight() / 12),
          size.left + (fontmap->getWidth() * 5), size.bottom);
  m_number_display = new cNumberBitmap(tmpsize, listener, tag, fontmap, 0);
  m_number_display->blank();
  m_number_display->setBackground(true);
  frame->addView(m_number_display);
}

cSmartKnob::~cSmartKnob() {
}

void cSmartKnob::draw(CDrawContext *pContext) {
  if(isDirty()) {
    m_anim_knob->draw(pContext);
    m_number_display->draw(pContext);
    CControl::setDirty(false);
  }
}

void cSmartKnob::handleEvent(void *data) {
  // Always hide on event catch
  m_number_display->hide();
  m_number_display->blank();
}

void cSmartKnob::mouse(CDrawContext *pContext, CPoint &where, long button) {
  m_anim_knob->takeFocus(pContext);
  m_anim_knob->mouse(pContext, where, button);
}

void cSmartKnob::setDirty(const bool val) {
  CControl::setDirty(val);
}

void cSmartKnob::setNumber(float number) {
  m_number_display->setNumber(number);
}

void cSmartKnob::setPrecision(int left, int right) {
  m_number_display->setPrecision(left, right);
}

void cSmartKnob::setTag(long tag) {
  m_anim_knob->setTag(tag);
}

void cSmartKnob::setValue(float val) {
  m_anim_knob->setValue(val);
  CControl::setValue(val);
  setDirty(true);
}