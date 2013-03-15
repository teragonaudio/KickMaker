/*
  ==============================================================================

    Oscillator.cpp
    Created: 14 Mar 2013 9:53:45pm
    Author:  nik

  ==============================================================================
*/

#include "Oscillator.h"
#include "NoiseWave.h"
#include "SawtoothWave.h"
#include "SineWave.h"
#include "SquareWave.h"
#include "TriangleWave.h"

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
            break;
        case kTypeOscAttackAmp:
            break;
        case kTypeOscDecay:
            break;
        case kTypeOscDecayAmp:
            break;
        case kTypeOscSustain:
            break;
        case kTypeOscSustainAmp:
            break;
        case kTypeOscRelease:
            break;
        case kTypeOscVolume:
            break;
        default:
            volume = parameter->getValue();
            break;
    }
}
