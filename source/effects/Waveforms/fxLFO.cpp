/*
 *  fxLFO.cpp
 *  KickMaker
 *
 *  Created by Nik Reiman on 05.07.07.
 *  Copyright 2007 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxLFO_H
#include "fxLFO.h"
#endif

fxLFO::fxLFO(pluginCore *p) : fxSelectWave(p, fxLFO_NUM_PARAMS)
{
}

fxLFO::~fxLFO()
{
}

void fxLFO::process(float *inputs, int frames)
{
  if(!getParameter(fxLFO_PRM_ENABLE))
  {
    return;
  }
  
  float dummy = 0.0f;
  for(int i = 0; i < frames; ++i)
  {
    // We don't really use the input values anyways
    process(dummy);
  }
}

void fxLFO::process(float &input)
{
  if(!getParameter(fxLFO_PRM_ENABLE))
  {
    return;
  }
  
  float value;
  fxSelectWave::process(value);
  // The actual m_plugin reference doesn't matter... they all point to the same place
  fxSinewave::m_plugin->setParameter(getParameter(fxLFO_PRM_TARGET),
                                     value * getParameter(fxLFO_PRM_AMPLITUDE) +
                                     fxSinewave::m_plugin->getParameter(REQ_VALUE_RAW, fxLFO_PRM_TARGET));
}

void fxLFO::setType(int wavetype)
{
  int num_extra_params = fxLFO_NUM_PARAMS - fxLFO_PRM_AMPLITUDE + 1; // fenceposting in action!
  int old_values[num_extra_params];
  
  // Get values of extra parameters for current waveform
  for(int i = 0; i < num_extra_params; ++i)
  {
    old_values[i] = fxSelectWave::getParameter(i + fxLFO_PRM_AMPLITUDE);
  }
  
  fxSelectWave::setType(wavetype);
  
  // ..and now set these old values into the extra parameters in the new wave
  for(int i = 0; i < num_extra_params; ++i)
  {
    fxSelectWave::setParameter(i + fxLFO_PRM_AMPLITUDE, old_values[i]);
  }
}