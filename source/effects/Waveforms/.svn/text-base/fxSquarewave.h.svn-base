/*
 *  fxSquarewave.h
 *  KickMaker
 *
 *  Created by Nik Reiman on 07.08.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxSquarewave_H
#define __fxSquarewave_H

#ifndef __effectCore_H
#include "effectCore.h"
#endif

#include <math.h>

enum {
  fxSquarewave_PRM_FREQ,
  fxSquarewave_PRM_PHASE,
  fxSquarewave_PRM_SAMPLE_RATE,
  fxSquarewave_NUM_PARAMS
};

class fxSquarewave : public effectCore {
public:
  fxSquarewave(pluginCore *p, int num_params = fxSquarewave_NUM_PARAMS);
  ~fxSquarewave();
  
  void process(float &input);
protected:
    unsigned long m_index;
  bool m_state;
private:
};

#endif