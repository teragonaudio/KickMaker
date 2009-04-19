/*
 *  fxWhiteNoise.h
 *  KickMaker
 *
 *  Created by Nik Reiman on 26.02.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxWhiteNoise_H
#define __fxWhiteNoise_H

#ifndef __effectCore_H
#include "effectCore.h"
#endif

enum {
  fxWhiteNoise_PRM_NOISE_LEVEL,
  fxWhiteNoise_NUM_PARAMS
};

class fxWhiteNoise : public effectCore {
public:
  fxWhiteNoise(pluginCore *p);
  ~fxWhiteNoise();
  
  virtual void process(float *inputs, long frames);
  virtual void process(float &input);
protected:
private:
  float m_scale;
  int m_x1;
  int m_x2;
};

#endif