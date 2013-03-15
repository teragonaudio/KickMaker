/*
  ==============================================================================

    SineWave.h
    Created: 14 Mar 2013 9:54:07pm
    Author:  nik

  ==============================================================================
*/

#ifndef __SINEWAVE_H_E349931C__
#define __SINEWAVE_H_E349931C__

#include "Waveform.h"

class SineWave : public Waveform {
public:
    SineWave() {}
    virtual ~SineWave() {}

    void process(float* buffer, int numSamples);
};

#endif  // __SINEWAVE_H_E349931C__
