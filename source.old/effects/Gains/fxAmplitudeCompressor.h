/*
 *  fxAmplitudeCompressor.h
 *  KickMaker
 *
 *  Created by Nik Reiman on 20.04.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxAmplitudeCompressor_H
#define __fxAmplitudeCompressor_H

#ifndef __effectCore_H
#include "effectCore.h"
#endif

#include <math.h>

#define DEF_MAX_GAIN DB2LIN(6.0)

enum {
  fxAmplitudeCompressor_PRM_ATTACK_SHAPE,
  fxAmplitudeCompressor_PRM_ATTACK_GAIN,
  fxAmplitudeCompressor_PRM_RELEASE,
  fxAmplitudeCompressor_PRM_RATIO,
  fxAmplitudeCompressor_NUM_PARAMS
};

class fxAmplitudeCompressor : public effectCore {
  public:
    fxAmplitudeCompressor(pluginCore *p);
    ~fxAmplitudeCompressor();
    
    void process(float *in_left, float *in_right, long frames);
    void process(float *inputs, long frames);
    void process(float &input);
    void setGain(float factor);
  protected:
    float m_gain_factor;
  private:
};

#endif