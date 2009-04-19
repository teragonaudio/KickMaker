/*
 *  fxSquarewave.cpp
 *  KickMaker
 *
 *  Created by Nik Reiman on 07.08.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxSquarewave_H
#include "fxSquarewave.h"
#endif

fxSquarewave::fxSquarewave(pluginCore *p, int num_params) : effectCore(p, num_params) {
  m_index = 0;
  m_state = false;
}

fxSquarewave::~fxSquarewave() {
}

void fxSquarewave::process(float &input) {
  if(m_state) {
    input = -1.0;
  }
  else {
    input = 1.0;
  }
  
  if(m_index++ > *m_params[fxSquarewave_PRM_SAMPLE_RATE] / (*m_params[fxSquarewave_PRM_FREQ])) {
    m_state = !m_state;
    m_index = 0;
  }
}