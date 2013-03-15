/*
  ==============================================================================

    SquareWave.cpp
    Created: 14 Mar 2013 9:54:51pm
    Author:  nik

  ==============================================================================
*/

#include "SquareWave.h"

void SquareWave::process(float* buffer, int numSamples)
{
    for(int i = 0; i < numSamples; ++i) {
        buffer[i] = rising ? 1.0f : -1.0f;
        if(index++ > sampleRate / frequency) {
            rising = !rising;
            index = 0;
        }
    }
}
