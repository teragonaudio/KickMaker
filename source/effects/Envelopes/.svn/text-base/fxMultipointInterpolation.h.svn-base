/*
 *  fxMultipointInterpolation.h
 *  DualComp
 *
 *  Created by Nik Reiman on 03.07.07.
 *  Copyright 2007 Kemper Digital GmbH. All rights reserved.
 *
 */

#ifndef __fxMultipointInterpolation_H
#define __fxMultipointInterpolation_H

#ifndef __effectCore_H
#include "effectCore.h"
#endif

const int fxMultipointInterpolation_MAX_BUFFER = 8192;
const int fxMultipointInterpolation_DEF_POINTS = 3;

enum {
  fxMultipointInterpolation_NUM_POINTS,
  fxMultipointInterpolation_NUM_PARAMS
};

class fxMultipointInterpolation : public effectCore 
{
public:
  fxMultipointInterpolation(pluginCore *p);
  ~fxMultipointInterpolation();
  
  float getGain();
  inline void process(float &input);
  void process(float *inputs, long frames);
  void setParameter(int index, float value);
  
protected:
  float m_point_last, m_point_cur, m_point_next;
    
  float *m_y_values;
  float *m_x_values;
  
  float m_gain_values[fxMultipointInterpolation_MAX_BUFFER];
  long m_gain_values_index, m_gain_values_max;
  
  long m_num_samples;
};

#endif