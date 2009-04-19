/*
 *  fxSawtooth.h
 *  KickMaker
 *
 *  Created by Nik Reiman on 07.08.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxSawtooth_H
#define __fxSawtooth_H

#ifndef __effectCore_H
#include "effectCore.h"
#endif

enum {
  fxSawtooth_PRM_FREQ,
  fxSawtooth_PRM_PHASE,
  fxSawtooth_PRM_SAMPLE_RATE,
  fxSawtooth_NUM_PARAMS
};

class fxSawtooth : public effectCore {
public:
  fxSawtooth(pluginCore *p, int num_params = fxSawtooth_NUM_PARAMS);
  ~fxSawtooth();
  
  void process(float &input);
protected:
    unsigned long m_index;
private:
};

#endif