/*
  ==============================================================================

    NoiseWave.cpp
    Created: 14 Mar 2013 9:54:24pm
    Author:  nik

  ==============================================================================
*/

#include "NoiseWave.h"

void NoiseWave::process(float* buffer, int numSamples)
{
    for(int i = 0; i < numSamples; ++i) {
        x1 ^= x2;
        buffer[i] += x2;
        x2 += x1;
    }
}
