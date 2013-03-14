/*
 *  fxHighpoint.cpp
 *  DualComp
 *
 *  Created by Nik Reiman on 25.11.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxHighpoint_H
#include "fxHighpoint.h"
#endif

fxHighpoint::fxHighpoint(pluginCore *p, int num_params) : effectCore(p, num_params) {
  m_high_point = m_last_in = 0.0;
  
  m_point_last = 0.0;
  m_point_cur = 0.0;
  m_point_next = 0.0;
  
  m_peak_cur = 0.0;
  
  m_num_points = 0;
}

fxHighpoint::~fxHighpoint() {
}

float fxHighpoint::getGain() const {
  return m_peak_cur; // + ((float)m_num_points * m_slope);
}

inline void fxHighpoint::process(float &input) {
  m_point_last = m_point_cur;
  m_point_cur = m_point_next;
  m_point_next = fabs(input);
  ++m_num_points;
  
  if(m_point_cur >= m_point_last && m_point_cur >= m_point_next)
  {
    m_peak_cur = m_point_cur;
    m_num_points = 0;
  }
}