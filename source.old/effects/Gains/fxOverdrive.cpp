/*
 *  fxOverdrive.cpp - An overdrive class with soft clipping
 *
 *  Created by Nik Reiman on 01.03.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxOverdrive_H
#include "fxOverdrive.h"
#endif

fxOverdrive::fxOverdrive(pluginCore *p, int num_params) : effectCore(p, num_params) {
}

fxOverdrive::~fxOverdrive() {
}

void fxOverdrive::process(float *inputs, long frames) {
  float gain = getParameter(fxOverdrive_PRM_DRIVE) * MAX_DRIVE_FACTOR;
  
  if(gain <= 1.0) {
    return;
  }
  
  while(--frames >= 0) {
    *inputs *= gain;
    if(*inputs > MAX_VOLUME_POS) {
      *inputs = MAX_VOLUME_POS + (*inputs * DEF_SIGNAL_FACTOR);
    }
    else if(*inputs < 0 && *inputs < MAX_VOLUME_NEG) {
      *inputs = MAX_VOLUME_NEG + (*inputs * DEF_SIGNAL_FACTOR);
    }
    *inputs++;
  }
}