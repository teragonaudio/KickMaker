/*
 *  fxTriangle.h
 *  KickMaker
 *
 *  Created by Nik Reiman on 07.08.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxTriangle_H
#define __fxTriangle_H

#ifndef __effectCore_H
#include "effectCore.h"
#endif

enum {
  fxTriangle_PRM_FREQ,
  fxTriangle_PRM_PHASE,
  fxTriangle_PRM_SAMPLE_RATE,
  fxTriangle_NUM_PARAMS
};

class fxTriangle : public effectCore {
public:
  fxTriangle(pluginCore *p, int num_params = fxTriangle_NUM_PARAMS);
  ~fxTriangle();
  
  void process(float &input);
protected:
    unsigned long m_index;
  bool m_state;
private:
};

#endif