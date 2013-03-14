/*
 *  fxTriangle.cpp
 *  KickMaker
 *
 *  Created by Nik Reiman on 07.08.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxTriangle_H
#include "fxTriangle.h"
#endif

fxTriangle::fxTriangle(pluginCore *p, int num_params) : effectCore(p, num_params) {
  m_index = 0;
  m_state = true;
}

fxTriangle::~fxTriangle() {
}

void fxTriangle::process(float &input) {
  if(m_state)
  {
    input = 2.0 * m_index++ * *m_params[fxTriangle_PRM_FREQ] / (*m_params[fxTriangle_PRM_SAMPLE_RATE]);
    if(m_index > *m_params[fxTriangle_PRM_SAMPLE_RATE] / (*m_params[fxTriangle_PRM_FREQ] * 2.0))
    {
      m_state = false;
    }
  }
  else
  {
    input = 2.0 * m_index-- * *m_params[fxTriangle_PRM_FREQ] / (*m_params[fxTriangle_PRM_SAMPLE_RATE]);
    if(m_index == 0)
    {
      m_state = true;
    }
  }
}