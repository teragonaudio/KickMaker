/*
 *  cTextEditLockable.h
 *  KickMaker
 *
 *  Created by Nik Reiman on 14.03.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __cTextEditLockable_H
#define __cTextEditLockable_H

#ifndef __vstcontrols__
#include "vstcontrols.h"
#endif

class cTextEditLockable : public CTextEdit {
public:
  cTextEditLockable (const CRect &size, CControlListener *listener, long tag,
                     const char *txt, CBitmap *background, const long style);
  virtual ~cTextEditLockable ();
  virtual bool getEnabled() const;
  virtual void getText(char *txt) const;
  virtual void draw(CDrawContext *pContext);
  virtual void looseFocus(CDrawContext *pContext);   
  virtual void mouse(CDrawContext *pContext, CPoint &where, long button);
  void setEnabled(bool enabled);
  virtual void setText(char *txt);
  virtual void takeFocus(CDrawContext *pContext);         
protected:
    bool m_edit_enabled;
private:
};

#endif