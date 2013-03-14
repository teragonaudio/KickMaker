/*
 *  fxSplineInterpolator.cpp
 *  Convolver2
 *
 *  Created by Nik Reiman on 20.08.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxSplineInterpolator_H
#include "fxSplineInterpolator.h"
#endif

fxSplineInterpolator::fxSplineInterpolator(pluginCore *p) :
effectCore(p, fxSplineInterpolator_NUM_PARAMS) {
  EPARAM(fxSplineInterpolator_PRM_MIDDLE_POINTS) = 0;
}

fxSplineInterpolator::~fxSplineInterpolator() {
}

void fxSplineInterpolator::process(float *inputs, long frames) {
  for(int i = *m_params[fxSplineInterpolator_PRM_MIDDLE_POINTS] + 1;
      i < frames - *m_params[fxSplineInterpolator_PRM_MIDDLE_POINTS] - 1; ++i) {
  }
}