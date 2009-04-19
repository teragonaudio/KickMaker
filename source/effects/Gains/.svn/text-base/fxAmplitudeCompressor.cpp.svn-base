/*
 *  fxAmplitudeCompressor.cpp
 *  KickMaker
 *
 *  Created by Nik Reiman on 20.04.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxAmplitudeCompressor_H
#include "fxAmplitudeCompressor.h"
#endif

fxAmplitudeCompressor::fxAmplitudeCompressor(pluginCore *p) : effectCore(p, fxAmplitudeCompressor_NUM_PARAMS) {
  m_gain_factor = 1.0f;
}

fxAmplitudeCompressor::~fxAmplitudeCompressor() {
}

void fxAmplitudeCompressor::process(float *in_left, float *in_right, long frames) {
  for(int i = 0; i < frames; ++i) {
    process(in_left[i]);
    process(in_right[i]);
  }
}

void fxAmplitudeCompressor::process(float *inputs, long frames) {
  for(int i = 0; i < frames; ++i) {
    process(inputs[i]);
  }
}

inline void fxAmplitudeCompressor::process(float &input) {
  if(input) {
    // First amplify input
    float gain = exp(*m_params[fxAmplitudeCompressor_PRM_ATTACK_GAIN] *
                     (*m_params[fxAmplitudeCompressor_PRM_ATTACK_SHAPE] - fabs(input))) *
    *m_params[fxAmplitudeCompressor_PRM_RATIO] -
    *m_params[fxAmplitudeCompressor_PRM_ATTACK_SHAPE];
    if(gain > DEF_MAX_GAIN) {
      gain = DEF_MAX_GAIN;
    }
    else if(gain < 1.0) {
      gain = 1.0;
    }

    // apply sidechain signal factor
    input *= gain * m_gain_factor;
  }
}

void fxAmplitudeCompressor::setGain(float factor) {
  m_gain_factor = factor; //+= ((factor - m_gain_factor) * EPARAM(fxAmplitudeCompressor_PRM_RELEASE));
}