/*
 *  fxHipassFilter.cpp
 *  Convolver2
 *
 *  Created by Nik Reiman on 26.06.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxHipassFilter_H
#include "fxHipassFilter.h"
#endif

fxHipassFilter::fxHipassFilter(pluginCore *p, int num_params) :
effectCore(p, fxHipassFilter_NUM_PARAMS) {
  m_in_l_0 = m_in_l_1 = m_in_l_2 = 0.0f;
  m_out_l_1 = m_out_l_2 = 0.0f;
  m_in_r_0 = m_in_r_1 = m_in_r_2 = 0.0f;
  m_out_r_1 = m_out_r_2 = 0.0f;
  m_a1 = m_a2 = 0.0f;
  m_b1 = m_b2 = 0.0f;
}

fxHipassFilter::~fxHipassFilter() {
}

void fxHipassFilter::process(float *in_left, float *in_right, long frames) {
  for(int i = 0; i < frames; ++i) {
    m_in_l_2 = m_in_l_1;
    m_in_l_1 = m_in_l_0;
    m_in_l_0 = in_left[i];
    m_in_r_2 = m_in_r_1;
    m_in_r_1 = m_in_r_0;
    m_in_r_0 = in_right[i];
    
    in_left[i] = (m_a1 * m_in_l_0) + (m_a2 * m_in_l_1) + (m_a1 * m_in_l_2) -
                 (m_b1 * m_out_l_1) - (m_b2 * m_out_l_2);
    in_right[i] = (m_a1 * m_in_r_0) + (m_a2 * m_in_r_1) + (m_a1 * m_in_r_2) -
                  (m_b1 * m_out_r_1) - (m_b2 * m_out_r_2);
    
    m_out_l_2 = m_out_l_1;
    m_out_l_1 = in_left[i];
    m_out_r_2 = m_out_r_1;
    m_out_r_1 = in_right[i];
  }
}

void fxHipassFilter::recache() {
  float c = tan(M_PI * *m_params[fxHipassFilter_PRM_FREQ] /
                *m_params[fxHipassFilter_PRM_SAMPLE_RATE]);
  m_a1 = 1.0 /((1.0 + *m_params[fxHipassFilter_PRM_RESONANCE] * c) + (c * c));
  m_a2 = -2.0 * m_a1;
  m_b1 = 2.0 * m_a1 * ((c * c) - 1.0);
  m_b2 = m_a1 * (1.0 - (*m_params[fxHipassFilter_PRM_RESONANCE] * c) + (c * c));
}  