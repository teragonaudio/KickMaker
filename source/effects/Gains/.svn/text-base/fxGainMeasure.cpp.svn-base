/*
 *  fxGainMeasure.cpp
 *  DualComp
 *
 *  Created by Nik Reiman on 12.08.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxGainMeasure_H
#include "fxGainMeasure.h"
#endif

fxGainMeasure::fxGainMeasure(pluginCore *p) : effectCore(p, fxGainMeasure_NUM_PARAMS) {
  m_num_points = 0;
  m_last_gain = 0.0;
  m_highest_gain = 0.0;
  m_total = 0.0;
}

fxGainMeasure::~fxGainMeasure() {
}

void fxGainMeasure::calcGain() {
  if(m_num_points) {
    m_last_gain = (float)(m_total / m_num_points);
    if(m_last_gain > m_highest_gain) {
      m_highest_gain = m_last_gain;
    }
  }
}

float fxGainMeasure::getAvgGain() const {
  return m_last_gain;
}

float fxGainMeasure::getRelGain() const {
  if(m_highest_gain) {
    return m_last_gain / m_highest_gain;
  }
  else {
    return 0.0;
  }
}

void fxGainMeasure::process(float &input) {
  m_total += fabs(input);
  if(++m_num_points > *m_params[fxGainMeasure_PRM_NUM_POINTS]) {
    calcGain();
    m_total = 0.0;
    m_num_points = 0;
  }
}

void fxGainMeasure::process(float *inputs, long frames) {
  for(int i = 0; i < frames; ++i) {
    process(inputs[i]);
  }
}