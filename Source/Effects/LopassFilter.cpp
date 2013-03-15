/*
  ==============================================================================

    LopassFilter.cpp
    Created: 14 Mar 2013 9:56:02pm
    Author:  nik

  ==============================================================================
*/

#include <math.h>
#include "LopassFilter.h"

LopassFilter::LopassFilter() : BufferProcessor()
{
    inputs0 = inputs1 = inputs2 = 0.0f;
    outputs1 = outputs2 = 0.0f;
    coefficientA1 = coefficientA2 = 0.0f;
    coefficientB1 = coefficientB2 = 0.0f;
}

void LopassFilter::process(float* buffer, int numSamples)
{
    for(int i = 0; i < numSamples; ++i) {
        inputs2 = inputs1;
        inputs1 = inputs0;
        inputs0 = buffer[i];

        buffer[i] = (coefficientA1 * inputs0) + (coefficientA2 + inputs1) + (coefficientA1 * inputs2) -
            (coefficientB1 * outputs1) - (coefficientB2 * outputs2);

        outputs2 = outputs1;
        outputs1 = buffer[i];
    }
}

void LopassFilter::calculateCoefficients()
{
    float c = 1.0f / tan(M_PI * frequency * sampleRate);
    coefficientA1 = 1.0f / (1.0f + (resonance * c) + (c * c));
    coefficientA2 = 2.0f * coefficientA1;
    coefficientB1 = 2.0f * coefficientA1 * (1.0f - (c * c));
    coefficientB2 = coefficientA1 * (1.0f - (resonance * c) + (c * c));
}
