/*
 *  fxSawtooth.cpp
 *  KickMaker
 *
 *  Created by Nik Reiman on 07.08.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxSawtooth_H
#include "fxSawtooth.h"
#endif

fxSawtooth::fxSawtooth(pluginCore *p, int num_params) : effectCore(p, num_params) {
  m_index = 0;
}

fxSawtooth::~fxSawtooth() {
}

void fxSawtooth::process(float &input) {
  input = m_index * *m_params[fxSawtooth_PRM_FREQ] / *m_params[fxSawtooth_PRM_SAMPLE_RATE];
  
  if(m_index++ > *m_params[fxSawtooth_PRM_SAMPLE_RATE] / *m_params[fxSawtooth_PRM_FREQ]) {
    m_index = 0;
  }
}