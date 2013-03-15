/*
  ==============================================================================

    LopassFilter.h
    Created: 14 Mar 2013 9:56:02pm
    Author:  nik

  ==============================================================================
*/

#ifndef __LOPASSFILTER_H_91D21A5E__
#define __LOPASSFILTER_H_91D21A5E__

#include "../BufferProcessor.h"

class LopassFilter : public BufferProcessor {
public:
    LopassFilter();
    virtual ~LopassFilter() {}

    void process(float* buffer, int numSamples);

    void setFrequency(float inFrequency) { frequency = inFrequency; calculateCoefficients(); }
    void setResonance(float inResonance) { resonance = inResonance; calculateCoefficients(); }
    void setSampleRate(double inSampleRate) { sampleRate = inSampleRate; calculateCoefficients(); }

private:
    void calculateCoefficients();

private:
    double sampleRate;
    float frequency;
    float resonance;

    float inputs0, inputs1, inputs2;
    float outputs1, outputs2;

    float coefficientA1, coefficientA2;
    float coefficientB1, coefficientB2;
};

#endif  // __LOPASSFILTER_H_91D21A5E__
