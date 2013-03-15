/*
  ==============================================================================

    SawtoothWave.h
    Created: 14 Mar 2013 9:55:09pm
    Author:  nik

  ==============================================================================
*/

#ifndef __SAWTOOTHWAVE_H_250B66CA__
#define __SAWTOOTHWAVE_H_250B66CA__

#include "Waveform.h"

class SawtoothWave : public Waveform {
public:
    SawtoothWave() : Waveform() {}
    virtual ~SawtoothWave() {}

    void process(float* buffer, int numSamples);
};

#endif  // __SAWTOOTHWAVE_H_250B66CA__
