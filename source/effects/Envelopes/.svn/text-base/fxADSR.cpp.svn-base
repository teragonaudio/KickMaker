/*
 *  fxADSR.cpp
 *  KickMaker
 *
 *  Created by Nik Reiman on 07.02.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxADSR_H
#include "fxADSR.h"
#endif

fxADSR::fxADSR(pluginCore *p) : effectCore(p, fxADSR_NUM_PARAMS) {
  m_current_index = 0;
  m_attack_intercept = 0.0;
}

fxADSR::~fxADSR() {
}

long fxADSR::getCurrentIndex() const {
  return m_current_index;
}

long fxADSR::getLength() const {
  return m_attack_index + m_decay_index + m_sustain_index + m_release_index;
}

inline void fxADSR::process(float *inputs, long frames) {
  for(int i = 0; i < frames; ++i) {
    process(inputs[i]);
  }
}

inline void fxADSR::process(float &input) {
  if(m_current_index < m_attack_index) {
    input *= (m_attack_slope * m_current_index++) + m_attack_intercept;
  }
  else if(m_current_index >= m_attack_index && m_current_index < m_decay_index) {
    input *= ((m_decay_slope * m_current_index++) + m_decay_intercept);
  }
  else if(m_current_index >= m_decay_index && m_current_index < m_sustain_index) {
    input *= ((m_sustain_slope * m_current_index++) + m_sustain_intercept);
  }
  else if(m_current_index >= m_sustain_index && m_current_index < m_release_index) {
    input *= ((m_release_slope * m_current_index++) + m_release_intercept);
  }
  else {
    input = 0.0;
    ++m_current_index;
  }
}

void fxADSR::recache() {
  m_attack_index = (long)(getParameter(fxADSR_PRM_ATTACK) * MAX_SEGMENT_LENGTH *
                          getParameter(fxADSR_PRM_SAMPLE_RATE));
  m_decay_index = m_attack_index + (long)(getParameter(fxADSR_PRM_DECAY) * MAX_SEGMENT_LENGTH *
                                          getParameter(fxADSR_PRM_SAMPLE_RATE));
  m_sustain_index = m_decay_index + (long)(getParameter(fxADSR_PRM_SUSTAIN) * MAX_SEGMENT_LENGTH *
                                           getParameter(fxADSR_PRM_SAMPLE_RATE));
  m_release_index = m_sustain_index + (long)(getParameter(fxADSR_PRM_RELEASE) * MAX_SEGMENT_LENGTH *
                                             getParameter(fxADSR_PRM_SAMPLE_RATE));
  
  m_attack_slope = getParameter(fxADSR_PRM_ATTACK_AMP) / m_attack_index;
  
  m_decay_slope = (getParameter(fxADSR_PRM_DECAY_AMP) - getParameter(fxADSR_PRM_ATTACK_AMP)) /
    (m_decay_index - m_attack_index);
  m_decay_intercept = getParameter(fxADSR_PRM_ATTACK_AMP) - (m_decay_slope * m_attack_index);
  
  m_sustain_slope = (getParameter(fxADSR_PRM_SUSTAIN_AMP) - getParameter(fxADSR_PRM_DECAY_AMP)) /
    (m_sustain_index - m_decay_index);
  m_sustain_intercept = getParameter(fxADSR_PRM_DECAY_AMP) - (m_sustain_slope * m_decay_index);
  
  m_release_slope = (0.0 - getParameter(fxADSR_PRM_SUSTAIN_AMP)) / (m_release_index - m_sustain_index);
  m_release_intercept = getParameter(fxADSR_PRM_SUSTAIN_AMP) - (m_release_slope * m_sustain_index);  
}

void fxADSR::reset() {
  m_current_index = 0;
}

void fxADSR::setAttackIntercept(double value) {
  m_attack_intercept = value;
}

void fxADSR::setCurrentIndex(long value) {
  m_current_index = value;
}