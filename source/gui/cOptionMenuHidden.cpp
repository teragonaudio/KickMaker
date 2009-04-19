/*
 *  cOptionMenuHidden.cpp
 *  KickMaker
 *
 *  Created by Nik Reiman on 19.04.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __cOptionMenuHidden_H
#include "cOptionMenuHidden.h"
#endif


cOptionMenuHidden::cOptionMenuHidden(const CRect &size, CControlListener *listener, long tag,
                                     CBitmap *background, CBitmap *bgWhenClick, const long style) :
COptionMenu(size, listener, tag, background, bgWhenClick, style) {
  m_submenu_items = 0;
}

cOptionMenuHidden::~cOptionMenuHidden() {
  for(int i = 0; i < m_submenu_items; ++i) {
    delete m_submenu_names.at(i);
  }
}

void cOptionMenuHidden::addSubmenu(const char *name, const char *parent) {
  COptionMenu *tmenu = new COptionMenu(size, listener, tag);
  
  if(parent == NULL) {
    addEntry(tmenu, (char*)name);
  }
  else {
    getSubMenu(findSubmenu(parent))->addEntry(tmenu, (char*)name);
  }
  
  char *tname = new char[MAX_MENU_NAME];
  strncpy(tname, name, MAX_MENU_NAME);
  m_submenu_names.push_back(tname);
  ++m_submenu_items;
}

long cOptionMenuHidden::findSubmenu(const char *name) {
  for(long i = 0; i < m_submenu_items; ++i) {
    if(!strcmp(name, m_submenu_names.at(i))) {
      return i;
    }
  }
  return -1;
}

void cOptionMenuHidden::draw(CDrawContext *pContext) {
  // This space intentionally left blank
  setDirty(false);
}