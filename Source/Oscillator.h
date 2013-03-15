/*
  ==============================================================================

    Oscillator.h
    Created: 14 Mar 2013 9:53:45pm
    Author:  nik

  ==============================================================================
*/

#ifndef __OSCILLATOR_H_A19FA352__
#define __OSCILLATOR_H_A19FA352__

#include "PluginParameters.h"
#include "BufferProcessor.h"
#include "Waveforms/Waveform.h"
#include "Effects/AdsrEnvelope.h"

using namespace teragon;

static const int kNumWaveforms = 5;

enum {
    kTypeOscOn,
    kTypeOscType,
    kTypeOscDetune,
    kTypeOscDetuneFine,
    kTypeOscExpand,
    kTypeOscExpandRate,
    kTypeOscPhase,
    kTypeOscAttack,
    kTypeOscAttackAmp,
    kTypeOscDecay,
    kTypeOscDecayAmp,
    kTypeOscSustain,
    kTypeOscSustainAmp,
    kTypeOscRelease,
    kTypeOscVolume
};

class Oscillator : public BufferProcessor, public PluginParameterObserver {
public:
    Oscillator();
    virtual ~Oscillator();

    void observeParameters(PluginParameterSet& parameters);
    void onParameterUpdated(const PluginParameter* parameter);

    void process(float* buffer, int numSamples);

    void setFrequency(float inFrequency);
    void setPhase(float inPhase);
    void setSampleRate(double sampleRate);

private:
    Waveform* waveforms[kNumWaveforms];
    Waveform* currentWaveform;
    bool enabled;
    float volume;
};

#endif  // __OSCILLATOR_H_A19FA352__
