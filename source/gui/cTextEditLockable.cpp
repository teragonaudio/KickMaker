/*
 *  cTextEditLockable.cpp
 *  KickMaker
 *
 *  Created by Nik Reiman on 14.03.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __cTextEditLockable_H
#include "cTextEditLockable.h"
#endif

cTextEditLockable::cTextEditLockable(const CRect &size, CControlListener *listener, long tag,
                                     const char *txt, CBitmap *background, const long style) :
CTextEdit(size, listener, tag, txt, background, style) {
  m_edit_enabled = false;
  setTransparency(true);
  setTextTransparency(true);
  
  setBackColor(kWhiteCColor);
  setFrameColor(kTransparentCColor);
#ifdef MAC
  setFont(kNormalFontSmall);
#else
  setFont(kNormalFont);
#endif
  setFontColor(kBlackCColor);
  setTxtFace(kBoldFace);
}

cTextEditLockable::~cTextEditLockable() {
}

bool cTextEditLockable::getEnabled() const {
  return m_edit_enabled;
}

void cTextEditLockable::getText(char *txt) const {
  CTextEdit::getText(txt);
}

void cTextEditLockable::draw(CDrawContext *pContext) {
  if(m_edit_enabled) {
    CTextEdit::draw(pContext);
  }
  setDirty(false);
}

void cTextEditLockable::looseFocus(CDrawContext *pContext) {
  if(m_edit_enabled) {
    CTextEdit::looseFocus(pContext);
    m_edit_enabled = false;
    
    // If the text is not changed, this control will not do this by default...
    if(listener) {
			listener->valueChanged(pContext, this);
    }
  }
}

void cTextEditLockable::mouse(CDrawContext *pContext, CPoint &where, long button) {
  if(m_edit_enabled) {
    CTextEdit::mouse(pContext, where, button);
  }
}

void cTextEditLockable::setEnabled(bool enabled) {
  m_edit_enabled = enabled;
}

void cTextEditLockable::setText(char *txt) {
  CTextEdit::setText(txt);
}

void cTextEditLockable::takeFocus(CDrawContext *pContext) {
  if(m_edit_enabled) {
    CTextEdit::takeFocus(pContext);
  }
}