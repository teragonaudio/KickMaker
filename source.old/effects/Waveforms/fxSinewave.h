/*
 *  fxSinewave.h
 *  KickMaker
 *
 *  Created by Nik Reiman on 06.08.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxSinewave_H
#define __fxSinewave_H

#ifndef __effectCore_H
#include "effectCore.h"
#endif

#include <math.h>

enum {
  fxSinewave_PRM_FREQ,
  fxSinewave_PRM_PHASE,
  fxSinewave_PRM_SAMPLE_RATE,
  fxSinewave_NUM_PARAMS
};

class fxSinewave : public effectCore {
public:
  fxSinewave(pluginCore *p, int num_params = fxSinewave_NUM_PARAMS);
  ~fxSinewave();
  
  void process(float &input);
protected:
    float m_scaler;
  unsigned long m_index;
private:
};

#endif