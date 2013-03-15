/*
  ==============================================================================

    NoiseWave.h
    Created: 14 Mar 2013 9:54:24pm
    Author:  nik

  ==============================================================================
*/

#ifndef __NOISEWAVE_H_E40692B5__
#define __NOISEWAVE_H_E40692B5__

#include "Waveform.h"

class NoiseWave : public Waveform {
public:
    NoiseWave() {}
    virtual ~NoiseWave() {}

    void process(float* buffer, int numSamples);
};

#endif  // __NOISEWAVE_H_E40692B5__
