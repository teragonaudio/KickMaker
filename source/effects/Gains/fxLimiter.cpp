/*
 *  fxLimiter.cpp
 *  Convolver2
 *
 *  Created by Nik Reiman on 29.06.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxLimiter_H
#include "fxLimiter.h"
#endif

fxLimiter::fxLimiter(pluginCore *p) : effectCore(p, fxLimiter_NUM_PARAMS) {
  *m_params[fxLimiter_PRM_THRESH] = 1.0;
}

fxLimiter::~fxLimiter() {
}

inline void fxLimiter::process(float &input) {
  if(input > *m_params[fxLimiter_PRM_THRESH]) {
    input = *m_params[fxLimiter_PRM_THRESH];
  }
}

void fxLimiter::process(float *inputs, long frames) {
  for(long i = 0; i < frames; ++i) {
    process(inputs[i]);
  }
}

void fxLimiter::process(float *in_left, float *in_right, long frames) {
  for(long i = 0; i < frames; ++i) {
    process(in_left[i]);
    process(in_right[i]);
  }
}