/*
 *  fxLopassFilter.h
 *  Convolver2
 *
 *  Created by Nik Reiman on 26.06.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxLopassFilter_H
#define __fxLopassFilter_H

#ifndef __effectCore_H
#include "effectCore.h"
#endif

enum {
  fxLopassFilter_PRM_FREQ,
  fxLopassFilter_PRM_RESONANCE, // Recommended range: { 0.1, 1.41421356237 }
  fxLopassFilter_PRM_SAMPLE_RATE,
  fxLopassFilter_NUM_PARAMS
};

class fxLopassFilter : public effectCore {
public:
  fxLopassFilter(pluginCore *p);
  ~fxLopassFilter();
  
  void process(float *inputs, long frames);
  void process(float *in_left, float *in_right, long frames);
  void recache();
protected:
  float m_in_l_0, m_in_l_1, m_in_l_2;
  float m_out_l_1, m_out_l_2;
  float m_in_r_0, m_in_r_1, m_in_r_2;
  float m_out_r_1, m_out_r_2;
  float m_a1, m_a2;
  float m_b1, m_b2;
private:
};

#endif