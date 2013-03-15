/*
  ==============================================================================

    Waveform.h
    Created: 15 Mar 2013 12:26:29am
    Author:  nik

  ==============================================================================
*/

#ifndef __WAVEFORM_H_18A500AF__
#define __WAVEFORM_H_18A500AF__

class Waveform {
public:
    Waveform() : frequency(20.0f), phase(0), sampleRate(44100.0f), index(0) {}
    virtual ~Waveform() {}

    virtual void process(float* buffer, int numSamples) = 0;

    virtual void setFrequency(float inFrequency) { this->frequency = inFrequency; }
    virtual void setPhase(float inPhase) { this->phase = inPhase; }
    virtual void setSampleRate(double inSampleRate) { this->sampleRate = inSampleRate; }

protected:
    float frequency;
    float phase;
    double sampleRate;
    int index;
};

#endif  // __WAVEFORM_H_18A500AF__
