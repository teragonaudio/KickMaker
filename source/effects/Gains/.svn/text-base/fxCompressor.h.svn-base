/*
 *  fxCompressor.h - Simple compression unit
 *
 *  Created by Nik Reiman on 03.03.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxCompressor_H
#define __fxCompressor_H

#ifndef __effectCore_H
#include "effectCore.h"
#endif

#include <math.h>

enum {
  fxCompressor_PRM_ATTACK,
  fxCompressor_PRM_RELEASE,
  fxCompressor_PRM_THRESH,
  fxCompressor_PRM_RATIO,
  fxCompressor_PRM_SAMPLE_RATE,
  fxCompressor_NUM_PARAMS
};

class fxCompressor : public effectCore {
public:
  fxCompressor(pluginCore *p);
  ~fxCompressor();
  
  virtual void process(float *inputs, long frames);
protected:
   const double lin2dB(double lin) const;
   const double dB2lin(double dB) const;

private:
     double m_envdb;
};

#endif