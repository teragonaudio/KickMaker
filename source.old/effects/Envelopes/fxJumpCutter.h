/*
 *  fxJumpCutter.h
 *  KickMaker
 *
 *  Created by Nik Reiman on 27.04.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxJumpCutter_H
#define __fxJumpCutter_H

#ifndef __effectCore_H
#include "effectCore.h"
#endif

class fxJumpCutter : public effectCore {
public:
  fxJumpCutter(pluginCore *p);
  ~fxJumpCutter();
  
  virtual void process(float &input);
  virtual void setBase(float value);
  virtual void setTarget(float value);
  virtual void setIndex(long index);
  virtual void setLength(long length);
protected:
  float m_base;
  float m_target;
  
  long m_index;
  long m_length;
private:
};

#endif