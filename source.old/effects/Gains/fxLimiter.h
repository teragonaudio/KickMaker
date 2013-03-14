/*
 *  fxLimiter.h
 *  Convolver2
 *
 *  Created by Nik Reiman on 29.06.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxLimiter_H
#define __fxLimiter_H

#ifndef __effectCore_H
#include "effectCore.h"
#endif

enum {
  fxLimiter_PRM_THRESH,
  fxLimiter_NUM_PARAMS
};

class fxLimiter : public effectCore {
public:
  fxLimiter(pluginCore *p);
  ~fxLimiter();
  
  virtual void process(float &input);
  virtual void process(float *inputs, long frames);
  virtual void process(float *in_left, float *in_right, long frames);
protected:
private:
};

#endif