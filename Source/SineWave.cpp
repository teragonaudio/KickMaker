/*
  ==============================================================================

    SineWave.cpp
    Created: 14 Mar 2013 9:54:07pm
    Author:  nik

  ==============================================================================
*/

#include <math.h>
#include "SineWave.h"

void SineWave::process(float* buffer, int numSamples)
{
    for(int i = 0; i < numSamples; ++i) {
        buffer[i] = sinf((2.0f * M_PI * index++ * frequency / sampleRate) + phase);
        if(index > sampleRate / frequency) {
            index = 0;
        }
    }
}
