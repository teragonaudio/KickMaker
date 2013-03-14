/*
 *  fxGainMeasure.h
 *  DualComp
 *
 *  Created by Nik Reiman on 12.08.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxGainMeasure_H
#define __fxGainMeasure_H

#ifndef __effectCore_H
#include "effectCore.h"
#endif

enum {
  fxGainMeasure_PRM_NUM_POINTS,
  fxGainMeasure_NUM_PARAMS
};

class fxGainMeasure : public effectCore {
public:
  fxGainMeasure(pluginCore *p);
  ~fxGainMeasure();
  
  void calcGain();
  float getAvgGain() const;
  float getRelGain() const;
  inline void process(float &input);
  void process(float *inputs, long frames);
protected:
  double m_total;
  float m_last_gain;
  float m_highest_gain;
  unsigned int m_num_points;
private:
};

#endif