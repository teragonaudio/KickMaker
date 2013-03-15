/*
  ==============================================================================

    WaveSmoother.h
    Created: 15 Mar 2013 7:34:06pm
    Author:  nik

  ==============================================================================
*/

#ifndef __WAVESMOOTHER_H_1489CD73__
#define __WAVESMOOTHER_H_1489CD73__

#include "../BufferProcessor.h"

class WaveSmoother : public BufferProcessor {
public:
    WaveSmoother() : BufferProcessor(), base(0.0f), target(0.0f), index(0), length(0) {}
    virtual ~WaveSmoother() {}

    void process(float* buffer, int numSamples);

    void setBase(float inBase) { base = inBase; }
    void setTarget(float inTarget) { target = inTarget; }
    void setIndex(int inIndex) { index = inIndex; }
    void setLength(int inLength) { length = inLength; }

private:
    float base;
    float target;

    int index;
    int length;
};


#endif  // __WAVESMOOTHER_H_1489CD73__
