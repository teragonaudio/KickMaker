/*
  ==============================================================================

    SquareWave.h
    Created: 14 Mar 2013 9:54:51pm
    Author:  nik

  ==============================================================================
*/

#ifndef __SQUAREWAVE_H_C8586E8__
#define __SQUAREWAVE_H_C8586E8__

#include "Waveform.h"

class SquareWave : public Waveform {
public:
    SquareWave() : Waveform(), rising(false) {}
    virtual ~SquareWave() {}

    void process(float* buffer, int numSamples);

private:
    bool rising;
};

#endif  // __SQUAREWAVE_H_C8586E8__
