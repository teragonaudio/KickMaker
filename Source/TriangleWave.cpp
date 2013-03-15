/*
  ==============================================================================

    TriangleWave.cpp
    Created: 14 Mar 2013 9:55:25pm
    Author:  nik

  ==============================================================================
*/

#include "TriangleWave.h"

void TriangleWave::process(float* buffer, int numSamples)
{
    for(int i = 0; i < numSamples; ++i) {
        if(rising) {
            buffer[i] = 2.0f * index++ * frequency / sampleRate;
            if(index > sampleRate / (frequency * 2.0f)) {
                rising = false;
            }
        }
        else {
            buffer[i] = 2.0f * index-- * frequency / sampleRate;
            if(index == 0) {
                rising = true;
            }
        }
    }
}
