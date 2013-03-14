/*
 *  fxSplineInterpolator.h
 *  Convolver2
 *
 *  Created by Nik Reiman on 20.08.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxSplineInterpolator_H
#define __fxSplineInterpolator_H

#ifndef __effectCore_H
#include "effectCore.h"
#endif

enum {
  fxSplineInterpolator_PRM_MIDDLE_POINTS,
  fxSplineInterpolator_NUM_PARAMS
};

class fxSplineInterpolator : public effectCore {
public:
  fxSplineInterpolator(pluginCore *p);
  ~fxSplineInterpolator();
  
  void process(float *inputs, long frames);
protected:
private:
};

#endif