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
    Waveform() : frequency(20.0f), sampleRate(44100.0f) {}
    virtual ~Waveform() {}

    virtual void process(float* buffer, int numSamples) = 0;

    virtual void setFrequency(float inFrequency) { this->frequency = inFrequency; }
    virtual void setPhase(float inPhase) { this->phase = inPhase; }
    virtual void setSampleRate(float inSampleRate) { this->sampleRate = inSampleRate; }

private:
    float frequency;
    float phase;
    float sampleRate;
};

#endif  // __WAVEFORM_H_18A500AF__
