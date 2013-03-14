/*
 *  fxOverdrive.h
 *  KickMaker
 *
 *  Created by Nik Reiman on 01.03.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxOverdrive_H
#define __fxOverdrive_H

#ifndef __effectCore_H
#include "effectCore.h"
#endif

#define DEF_SIGNAL_FACTOR 0.5
#define DEF_LEFT 0.25
#define DEF_RIGHT 0.75
#define MAX_DRIVE_FACTOR 10.0
#define MAX_VOLUME_POS 1.0
#define MAX_VOLUME_NEG -1.0

enum {
  fxOverdrive_PRM_DRIVE,
  fxOverdrive_PRM_FREQUENCY,
  fxOverdrive_PRM_SAMPLE_RATE,
  fxOverdrive_NUM_PARAMS
};

class fxOverdrive : public effectCore {
public:
  fxOverdrive(pluginCore *p, int num_params);
  ~fxOverdrive();
  
  virtual void process(float *inputs, long frames);
protected:
private:
};

#endif