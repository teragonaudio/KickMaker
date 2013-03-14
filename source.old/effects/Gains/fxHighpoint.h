/*
 *  fxHighpoint.h
 *  DualComp
 *
 *  Created by Nik Reiman on 25.11.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxHighpoint_H
#define __fxHighpoint_H

#ifndef __effectCore_H
#include "effectCore.h"
#endif

enum {
  fxHighpoint_NUM_PARAMS
};

class fxHighpoint : public effectCore {
public:
  fxHighpoint(pluginCore *p, int num_params = fxHighpoint_NUM_PARAMS);
  ~fxHighpoint();
  
  float getGain() const;
  void process(float &input);
protected:
private:
  float m_last_in;
  float m_high_point;

  float m_point_last;
  float m_point_cur;
  float m_point_next;
  
  float m_peak_last;
  float m_peak_cur;
  
  unsigned long m_num_points;
};

#endif