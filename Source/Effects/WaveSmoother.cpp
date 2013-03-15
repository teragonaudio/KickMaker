/*
  ==============================================================================

    WaveSmoother.cpp
    Created: 15 Mar 2013 7:34:06pm
    Author:  nik

  ==============================================================================
*/

#include <math.h>
#include "WaveSmoother.h"

void WaveSmoother::process(float* buffer, int numSamples)
{
    for(int i = 0; i < numSamples; ++i) {
        buffer[i] = cos(M_PI * index++ / length) * ((base - target) / 2.0f) + ((base + target) / 2.0f);
    }
}
