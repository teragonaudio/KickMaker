/*
 *  fxJumpCutter.cpp
 *  KickMaker
 *
 *  Created by Nik Reiman on 27.04.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxJumpCutter_H
#include "fxJumpCutter.h"
#endif

#include <math.h>

fxJumpCutter::fxJumpCutter(pluginCore *p) : effectCore(p, 0) {
  m_index = 0;
  m_length = 0;
  m_base = 0.0;
  m_target = 0.0;
}

fxJumpCutter::~fxJumpCutter() {
}

inline void fxJumpCutter::process(float &input) {
    input = cos(M_PI * m_index++ / m_length) * ((m_base - m_target) / 2.0) + ((m_base + m_target) / 2.0);
  
  /*float slope = -1.0 / frames; //(target - base) / frames;
  for(long i = 1; i < frames; ++i) {
    inputs[i] += (slope * i + 1.0) * base;
  }*/
}

void fxJumpCutter::setBase(float value) {
  m_base = value;
}

void fxJumpCutter::setTarget(float value) {
  m_target = value;
}

void fxJumpCutter::setIndex(long index) {
  m_index = index;
}

void fxJumpCutter::setLength(long length) {
  m_length = length;
}