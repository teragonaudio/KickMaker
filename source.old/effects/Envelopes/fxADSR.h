/*
 *  fxADSR.h
 *  KickMaker
 *
 *  Created by Nik Reiman on 07.02.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __fxADSR_H
#define __fxADSR_H

#ifndef __effectCore_H
#include "effectCore.h"
#endif

#define MAX_SEGMENT_LENGTH .25

enum {
  fxADSR_PRM_ATTACK,
  fxADSR_PRM_ATTACK_AMP,
  fxADSR_PRM_DECAY,
  fxADSR_PRM_DECAY_AMP,
  fxADSR_PRM_SUSTAIN,
  fxADSR_PRM_SUSTAIN_AMP,
  fxADSR_PRM_RELEASE,
  fxADSR_PRM_SAMPLE_RATE,
  fxADSR_NUM_PARAMS
};

class fxADSR : public effectCore {
public:
  fxADSR(pluginCore *p);
  ~fxADSR();
  
  long getCurrentIndex() const;
  long getLength() const;
  void process(float *inputs, long frames);
  void process(float &input);
  void recache();
  void reset();
  void setAttackIntercept(double value);
  void setCurrentIndex(long value);
  
protected:
private:
    double m_current_gain;
  
  double m_attack_slope;
  double m_decay_slope;
  double m_sustain_slope;
  double m_release_slope;
  
  double m_attack_intercept;
  double m_decay_intercept;
  double m_sustain_intercept;
  double m_release_intercept;
  
  long m_attack_index;
  long m_decay_index;
  long m_sustain_index;
  long m_release_index;

  long m_current_index;
};

#endif