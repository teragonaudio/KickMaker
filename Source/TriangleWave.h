/*
  ==============================================================================

    TriangleWave.h
    Created: 14 Mar 2013 9:55:25pm
    Author:  nik

  ==============================================================================
*/

#ifndef __TRIANGLEWAVE_H_F0C34D93__
#define __TRIANGLEWAVE_H_F0C34D93__

#include "Waveform.h"

class TriangleWave : public Waveform {
public:
    TriangleWave() {}
    virtual ~TriangleWave() {}

    void process(float* buffer, int numSamples);
};

#endif  // __TRIANGLEWAVE_H_F0C34D93__
