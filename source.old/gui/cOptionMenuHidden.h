/*
 *  cOptionMenuHidden.h
 *  KickMaker
 *
 *  Created by Nik Reiman on 19.04.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __cOptionMenuHidden_H
#define __cOptionMenuHidden_H

#ifndef __vstcontrols__
#include "vstcontrols.h"
#endif

#include <vector>

#define MAX_MENU_NAME 24

class cOptionMenuHidden : public COptionMenu {
public:
  cOptionMenuHidden(const CRect &size, CControlListener *listener, long tag, CBitmap *background = 0,
                    CBitmap *bgWhenClick = 0, const long style = 0);
  ~cOptionMenuHidden();
  
  virtual void addSubmenu(const char *name, const char *parent = NULL);
  virtual void draw(CDrawContext *pContext);
  virtual long findSubmenu(const char *name);
protected:
  int m_submenu_items;
  std::vector<char*> m_submenu_names;
private:
};

#endif