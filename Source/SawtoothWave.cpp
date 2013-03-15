/*
  ==============================================================================

    SawtoothWave.cpp
    Created: 14 Mar 2013 9:55:09pm
    Author:  nik

  ==============================================================================
*/

#include "SawtoothWave.h"

void SawtoothWave::process(float* buffer, int numSamples)
{
    for(int i = 0; i < numSamples; ++i) {
        buffer[i] = index++ * frequency / sampleRate;
        if(index > sampleRate / frequency) {
            index = 0;
        }
    }
}
