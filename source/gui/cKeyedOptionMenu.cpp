/*
 *  cKeyedOptionMenu.cpp
 *  KickMaker
 *
 *  Created by Nik Reiman on 30.03.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __cKeyedOptionMenu_H
#include "cKeyedOptionMenu.h"
#endif

cKeyedOptionMenu::cKeyedOptionMenu(const CRect &size, CControlListener *listener, long tag) :
COptionMenu(size, listener, tag, 0) {
  setFont(kNormalFontSmall);
  setTxtFace(kBoldFace);
  setFontColor(kBlackCColor);
  setBackColor(kTransparentCColor);
  setFrameColor(kTransparentCColor);
  setTransparency(true);
  setHoriAlign(kLeftText);
  
  m_num_keys = 0;
}

cKeyedOptionMenu::~cKeyedOptionMenu() {
}

int cKeyedOptionMenu::addKey(const char *name, long value) {
  struct _tKey k;
  strncpy(k.key, name, MAX_KEY_LENGTH);
  k.value = value;
  m_keys.push_back(k);
  m_num_keys = m_keys.size();
  
  addEntry((char*)name);
  
  return m_num_keys;
}

long cKeyedOptionMenu::getCurrentKey() const {
  int current = (int)getValue();
  if(current >= 0 && current < m_num_keys) {
    return m_keys.at(current).value;
  }
  return -1;
}

long cKeyedOptionMenu::getKey(long key) const {
  return m_keys.at(key).value;
}

void cKeyedOptionMenu::setKeyValue(long key, long value) {
  if(key >= 0 && key < m_num_keys) {
    m_keys.at(key).value = value;
  }
}