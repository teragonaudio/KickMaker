/*
 *  fxSinewave.cpp
 *  KickMaker
 *
 *  Created by Nik Reiman on 06.08.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxSinewave_H
#include "fxSinewave.h"
#endif

fxSinewave::fxSinewave(pluginCore *p, int num_params) : effectCore(p, num_params) {
  m_index = 0;
}

fxSinewave::~fxSinewave() {
}

inline void fxSinewave::process(float &input) {
  input = sinf((2.0 * M_PI * m_index++ * *m_params[fxSinewave_PRM_FREQ] / *m_params[fxSinewave_PRM_SAMPLE_RATE])
               + *m_params[fxSinewave_PRM_PHASE]);
  
  if(m_index > *m_params[fxSinewave_PRM_SAMPLE_RATE] / *m_params[fxSinewave_PRM_FREQ]) {
    m_index = 0;
  }
}