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
    NoiseWave() : Waveform(), x1(0x67452301), x2(0xefcdab89) {}
    virtual ~NoiseWave() {}

    void process(float* buffer, int numSamples);

private:
    int x1;
    int x2;
};

#endif  // __NOISEWAVE_H_E40692B5__
