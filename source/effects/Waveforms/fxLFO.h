/*
 *  fxLFO.h
 *  KickMaker
 *
 *  Created by Nik Reiman on 05.07.07.
 *  Copyright 2007 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxLFO_H
#define __fxLFO_H

#ifndef __fxSelectWave_H
#include "fxSelectWave.h"
#endif

enum {
  // Parameters common to all subwaves
  fxLFO_PRM_FREQ,
  fxLFO_PRM_PHASE,
  fxLFO_PRM_SAMPLE_RATE,
  // Parameters unique to the LFO
  fxLFO_PRM_AMPLITUDE,
  fxLFO_PRM_TARGET,
  fxLFO_PRM_ENABLE,
  fxLFO_NUM_PARAMS
};

class fxLFO : public fxSelectWave
{
public:
  fxLFO(pluginCore *p);
  ~fxLFO();
    
  virtual inline void process(float *inputs, int frames);
  virtual void process(float &input);
  virtual void setType(int wavetype);

protected:
private:
};

#endif