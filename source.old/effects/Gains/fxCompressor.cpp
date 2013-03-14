/*
 *  fxCompressor.cpp - A simple compression effect
 *
 *  Created by Nik Reiman on 03.03.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxCompressor_H
#include "fxCompressor.h"
#endif

fxCompressor::fxCompressor(pluginCore *p) : effectCore(p, fxCompressor_NUM_PARAMS) {
  m_envdb = DEF_DC_OFFSET;
}

fxCompressor::~fxCompressor() {
}

const inline double fxCompressor::lin2dB(double lin) const {
#define LOG_2_DB 8.6858896380650365530225783783321 // 20 / ln( 10 )
 return log(lin) * LOG_2_DB;
}

const inline double fxCompressor::dB2lin(double dB) const {
#define DB_2_LOG 0.11512925464970228420089957273422 // ln( 10 ) / 20
 return exp(dB * DB_2_LOG);
}

void fxCompressor::process(float *inputs, long frames) {
  double attack_coeff = exp(-1000.0 / (getParameter(fxCompressor_PRM_ATTACK) *
                                       getParameter(fxCompressor_PRM_SAMPLE_RATE)));
  double release_coeff = exp(-1000.0 / (getParameter(fxCompressor_PRM_RELEASE) *
                                        getParameter(fxCompressor_PRM_SAMPLE_RATE)));
  double keydb;
  double overdb;
  double gain;
  
  float t = getParameter(fxCompressor_PRM_THRESH);
  float r = getParameter(fxCompressor_PRM_RATIO);
  
  while(--frames >= 0) {
    keydb = lin2dB(fabs(*inputs) + DEF_DC_OFFSET);
    overdb = keydb - t;
    if(overdb < 0.0) {
      overdb = 0.0;
    }
    
    overdb += DEF_DC_OFFSET;
    if(m_envdb > overdb) {
      m_envdb = overdb + attack_coeff * (m_envdb - overdb);
    }
    else {
      m_envdb = overdb + release_coeff * (m_envdb - overdb);
    }
    // This is subtracted again to avoid denormalization after adding it
    overdb = m_envdb - DEF_DC_OFFSET;
    
    gain = overdb * (r - 1.0);
    gain = dB2lin(gain);
    
    *inputs++ *= gain;
  }
}