/*
 *  fxSelectWave.cpp
 *  KickMaker
 *
 *  Created by Nik Reiman on 05.07.07.
 *  Copyright 2007 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxSelectWave_H
#include "fxSelectWave.h"
#endif

fxSelectWave::fxSelectWave(pluginCore *p, int num_params) : fxSinewave(p, num_params),
fxSquarewave(p, num_params),
fxSawtooth(p, num_params),
fxTriangle(p, num_params)
{
  m_wavetype = WAV_SINE;
}

fxSelectWave::~fxSelectWave()
{
}

float fxSelectWave::getParameter(int index) const
{
  switch(m_wavetype)
  {
    case WAV_SINE:
      return fxSinewave::getParameter(index);
    case WAV_SQUARE:
      return fxSquarewave::getParameter(index);
    case WAV_SAWTOOTH:
      return fxSawtooth::getParameter(index);
    case WAV_TRIANGLE:
      return fxTriangle::getParameter(index);
    default:
      return 0.0f;
  }
}

void fxSelectWave::process(float &input)
{
  switch(m_wavetype)
  {
    case WAV_SINE:
      return fxSinewave::process(input);
    case WAV_SQUARE:
      return fxSquarewave::process(input);
    case WAV_SAWTOOTH:
      return fxSawtooth::process(input);
    case WAV_TRIANGLE:
      return fxTriangle::process(input);
  }
}

void fxSelectWave::linkParameter(int plugin_index, int effect_index)
{
  switch(m_wavetype)
  {
    case WAV_SINE:
      return fxSinewave::linkParameter(plugin_index, effect_index);
    case WAV_SQUARE:
      return fxSquarewave::linkParameter(plugin_index, effect_index);
    case WAV_SAWTOOTH:
      return fxSawtooth::linkParameter(plugin_index, effect_index);
    case WAV_TRIANGLE:
      return fxTriangle::linkParameter(plugin_index, effect_index);
  }
}

void fxSelectWave::linkParameter(float *target, int effect_index)
{
  switch(m_wavetype)
  {
    case WAV_SINE:
      return fxSinewave::linkParameter(target, effect_index);
    case WAV_SQUARE:
      return fxSquarewave::linkParameter(target, effect_index);
    case WAV_SAWTOOTH:
      return fxSawtooth::linkParameter(target, effect_index);
    case WAV_TRIANGLE:
      return fxTriangle::linkParameter(target, effect_index);
  }
}

void fxSelectWave::setParameter(int index, float value)
{
  switch(m_wavetype)
  {
    case WAV_SINE:
      return fxSinewave::setParameter(index, value);
    case WAV_SQUARE:
      return fxSquarewave::setParameter(index, value);
    case WAV_SAWTOOTH:
      return fxSawtooth::setParameter(index, value);
    case WAV_TRIANGLE:
      return fxTriangle::setParameter(index, value);
  }
}

void fxSelectWave::setType(int wavetype)
{
  if(wavetype >= 0 && wavetype < WAV_LAST_WAV)
  {
    m_wavetype = wavetype;
  }
}