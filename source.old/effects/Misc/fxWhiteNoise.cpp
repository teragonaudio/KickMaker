/*
 *  fxWhiteNoise.cpp
 *  KickMaker
 *
 *  Created by Nik Reiman on 26.02.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxWhiteNoise_H
#include "fxWhiteNoise.h"
#endif

fxWhiteNoise::fxWhiteNoise(pluginCore *p) : effectCore(p, fxWhiteNoise_NUM_PARAMS) {
  m_scale = 2.0f / 0xffffffff;
  m_x1 = 0x67452301;
  m_x2 = 0xefcdab89;
}

fxWhiteNoise::~fxWhiteNoise() {
}

inline void fxWhiteNoise::process(float *inputs, long frames) {
  float outscale = getParameter(fxWhiteNoise_PRM_NOISE_LEVEL) * m_scale;
  
  while(--frames) {
    m_x1 ^= m_x2;
    *inputs++ += m_x2 * outscale;
    m_x2 += m_x1;
  }
}

inline void fxWhiteNoise::process(float &input) {
  float outscale = getParameter(fxWhiteNoise_PRM_NOISE_LEVEL) * m_scale;
  
  m_x1 ^= m_x2;
  input += m_x2 * outscale;
  m_x2 += m_x1;
}