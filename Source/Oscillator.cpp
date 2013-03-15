/*
  ==============================================================================

    Oscillator.cpp
    Created: 14 Mar 2013 9:53:45pm
    Author:  nik

  ==============================================================================
*/

#include "Oscillator.h"
#include "Waveforms/NoiseWave.h"
#include "Waveforms/SawtoothWave.h"
#include "Waveforms/SineWave.h"
#include "Waveforms/SquareWave.h"
#include "Waveforms/TriangleWave.h"

Oscillator::Oscillator()
{
    waveforms[0] = new SineWave();
    waveforms[1] = new SquareWave();
    waveforms[2] = new TriangleWave();
    waveforms[3] = new SawtoothWave();
    waveforms[4] = new NoiseWave();
    currentWaveform = waveforms[0];
}

Oscillator::~Oscillator()
{
    for(int i = 0; i < kNumWaveforms; ++i) {
        delete waveforms[i];
    }
}

void Oscillator::observeParameters(PluginParameterSet& parameters)
{
    for(int i = 0; i < parameters.size(); ++i) {
        parameters[i]->addObserver(this);
    }
}

void Oscillator::onParameterUpdated(const PluginParameter* parameter)
{
    switch(parameter->getType()) {
        case kTypeOscOn:
            enabled = parameter->getValue();
            break;
        case kTypeOscType:
            currentWaveform = waveforms[(int)parameter->getValue()];
            break;
        case kTypeOscDetune:
            break;
        case kTypeOscDetuneFine:
            break;
        case kTypeOscExpand:
            break;
        case kTypeOscExpandRate:
            break;
        case kTypeOscPhase:
            break;
        case kTypeOscAttack:
            adsrEnvelope.setAttack(parameter->getValue());
            break;
        case kTypeOscAttackAmp:
            adsrEnvelope.setAttackAmp(parameter->getValue());
            break;
        case kTypeOscDecay:
            adsrEnvelope.setDecay(parameter->getValue());
            break;
        case kTypeOscDecayAmp:
            adsrEnvelope.setDecayAmp(parameter->getValue());
            break;
        case kTypeOscSustain:
            adsrEnvelope.setSustain(parameter->getValue());
            break;
        case kTypeOscSustainAmp:
            adsrEnvelope.setSustainAmp(parameter->getValue());
            break;
        case kTypeOscRelease:
            adsrEnvelope.setRelease(parameter->getValue());
            break;
        case kTypeOscVolume:
            gain = parameter->getValue();
            break;
        default:
            break;
    }
}

void Oscillator::process(float* buffer, int numSamples)
{
    currentWaveform->process(buffer, numSamples);
    adsrEnvelope.process(buffer, numSamples);

    for(int i = 0; i < numSamples; ++i) {
        buffer[i] *= gain;
    }
}

void Oscillator::setFrequency(float inFrequency)
{
    for(int i = 0; i < kNumWaveforms; ++i) {
        waveforms[i]->setFrequency(inFrequency);
    }
}

void Oscillator::setPhase(float inPhase)
{
    for(int i = 0; i < kNumWaveforms; ++i) {
        waveforms[i]->setPhase(inPhase);
    }
}

void Oscillator::setSampleRate(double inSampleRate)
{
    for(int i = 0; i < kNumWaveforms; ++i) {
        waveforms[i]->setSampleRate(inSampleRate);
    }

    adsrEnvelope.setSampleRate(inSampleRate);
}

