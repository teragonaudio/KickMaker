/*
  ==============================================================================

    Compressor.cpp
    Created: 14 Mar 2013 9:55:40pm
    Author:  nik

  ==============================================================================
*/

#include "Compressor.h"

void Compressor::process(float* buffer, int numSamples)
{
    double keyDb;
    double overDb;
    double gain;

    for(int i = 0; i < numSamples; ++i) {
        keyDb = linear2dB(fabs(buffer[i]) + kDcOffset);
        overDb = keyDb - threshold;
        if(overDb < 0.0) {
            overDb = 0.0;
        }

        overDb += kDcOffset;
        if(envDb > overDb) {
            envDb = overDb + attackCoefficient * (envDb - overDb);
        }
        else {
            envDb = overDb + releaseCoefficient * (envDb - overDb);
        }

        // Subtract the DC offset again to avoid denormalization
        overDb = envDb - kDcOffset;
        gain = db2linear(overDb * (ratio - 1.0f));

        buffer[i] *= gain;
    }
}

void Compressor::calculateCoefficients()
{
    attackCoefficient = exp(-1000.0 / (attack * sampleRate));
    releaseCoefficient = exp(-1000.0 / (release * sampleRate));
}
