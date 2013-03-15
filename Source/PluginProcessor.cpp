/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

static const double kMaxPhase = 6.28318530718; // 2 * Pi
static const double kMaxAdsr = 0.5;
static const double kMinAdsr = 0.01;

//==============================================================================
static void addOscParameter(PluginParameter *parameter, int parameterType,
                            PluginParameterSet& parameters, PluginParameterSet& oscParameterSet)
{
    parameter->setType(parameterType);
    parameters.add(parameter);
    oscParameterSet.add(parameter);
}

KickMakerAudioProcessor::KickMakerAudioProcessor()
{
    PluginParameter *p;

    PluginParameterSet osc1Params;
    addOscParameter(new BooleanParameter("Osc 1 On", true), kTypeOscOn, parameters, osc1Params);
    addOscParameter(new IntegerParameter("Osc 1 Type", 0, kNumWaveforms - 1, 0), kTypeOscType, parameters, osc1Params);
    addOscParameter(new FloatParameter("Osc 1 Detune", -40.0, 40.0, 0.0), kTypeOscDetune, parameters, osc1Params);
    addOscParameter(new FloatParameter("Osc 1 Detune Fine", -1.0, 1.0, 0.0), kTypeOscDetuneFine, parameters, osc1Params);
    addOscParameter(new IntegerParameter("Osc 1 Expand", 0, 100, 0), kTypeOscExpand, parameters, osc1Params);
    addOscParameter(new FloatParameter("Osc 1 Expand Rate", 1.0, 100.0, 1.0), kTypeOscExpandRate, parameters, osc1Params);
    addOscParameter(new FloatParameter("Osc 1 Phase", 0.0, kMaxPhase, 0.0), kTypeOscPhase, parameters, osc1Params);
    addOscParameter(new FloatParameter("Osc 1 Attack", kMinAdsr, kMaxAdsr, 0.05), kTypeOscAttack, parameters, osc1Params);
    addOscParameter(new FloatParameter("Osc 1 Attack Amp", 0.0, 1.0, 0.84), kTypeOscAttackAmp, parameters, osc1Params);
    addOscParameter(new FloatParameter("Osc 1 Decay", kMinAdsr, kMaxAdsr, 0.5), kTypeOscDecay, parameters, osc1Params);
    addOscParameter(new FloatParameter("Osc 1 Decay Amp", 0.0, 1.0, 0.475), kTypeOscDecayAmp, parameters, osc1Params);
    addOscParameter(new FloatParameter("Osc 1 Sustain", kMinAdsr, kMaxAdsr, 0.25), kTypeOscSustain, parameters, osc1Params);
    addOscParameter(new FloatParameter("Osc 1 Sustain Amp", 0.0, 1.0, 0.145), kTypeOscSustainAmp, parameters, osc1Params);
    addOscParameter(new FloatParameter("Osc 1 Release", kMinAdsr, kMaxAdsr, 0.5), kTypeOscRelease, parameters, osc1Params);
    addOscParameter(new DecibelParameter("Osc 1 Volume", -60.0, 0.0, 0.0), kTypeOscVolume, parameters, osc1Params);
    oscillators[0].observeParameters(osc1Params);

    PluginParameterSet osc2Params;
    addOscParameter(new BooleanParameter("Osc 2 On", true), kTypeOscOn, parameters, osc2Params);
    addOscParameter(new IntegerParameter("Osc 2 Type", 0, kNumWaveforms - 1, 0), kTypeOscType, parameters, osc2Params);
    addOscParameter(new FloatParameter("Osc 2 Detune", -40.0, 40.0, 0.0), kTypeOscDetune, parameters, osc2Params);
    addOscParameter(new FloatParameter("Osc 2 Detune Fine", -1.0, 1.0, 0.0), kTypeOscDetuneFine, parameters, osc2Params);
    addOscParameter(new IntegerParameter("Osc 2 Expand", 0, 100, 0), kTypeOscExpand, parameters, osc2Params);
    addOscParameter(new FloatParameter("Osc 2 Expand Rate", 1.0, 100.0, 1.0), kTypeOscExpandRate, parameters, osc2Params);
    addOscParameter(new FloatParameter("Osc 2 Phase", 0.0, kMaxPhase, 0.0), kTypeOscPhase, parameters, osc2Params);
    addOscParameter(new FloatParameter("Osc 2 Attack", kMinAdsr, kMaxAdsr, 0.05), kTypeOscAttack, parameters, osc2Params);
    addOscParameter(new FloatParameter("Osc 2 Attack Amp", 0.0, 1.0, 0.84), kTypeOscAttackAmp, parameters, osc2Params);
    addOscParameter(new FloatParameter("Osc 2 Decay", kMinAdsr, kMaxAdsr, 0.5), kTypeOscDecay, parameters, osc2Params);
    addOscParameter(new FloatParameter("Osc 2 Decay Amp", 0.0, 1.0, 0.475), kTypeOscDecayAmp, parameters, osc2Params);
    addOscParameter(new FloatParameter("Osc 2 Sustain", kMinAdsr, kMaxAdsr, 0.25), kTypeOscSustain, parameters, osc2Params);
    addOscParameter(new FloatParameter("Osc 2 Sustain Amp", 0.0, 1.0, 0.145), kTypeOscSustainAmp, parameters, osc2Params);
    addOscParameter(new FloatParameter("Osc 2 Release", kMinAdsr, kMaxAdsr, 0.5), kTypeOscRelease, parameters, osc2Params);
    addOscParameter(new DecibelParameter("Osc 2 Volume", -60.0, 0.0, 0.0), kTypeOscVolume, parameters, osc2Params);
    oscillators[1].observeParameters(osc1Params);

    PluginParameterSet osc3Params;
    addOscParameter(new BooleanParameter("Osc 3 On", true), kTypeOscOn, parameters, osc3Params);
    addOscParameter(new IntegerParameter("Osc 3 Type", 0, kNumWaveforms - 1, 0), kTypeOscType, parameters, osc3Params);
    addOscParameter(new FloatParameter("Osc 3 Detune", -40.0, 40.0, 0.0), kTypeOscDetune, parameters, osc3Params);
    addOscParameter(new FloatParameter("Osc 3 Detune Fine", -1.0, 1.0, 0.0), kTypeOscDetuneFine, parameters, osc3Params);
    addOscParameter(new IntegerParameter("Osc 3 Expand", 0, 100, 0), kTypeOscExpand, parameters, osc3Params);
    addOscParameter(new FloatParameter("Osc 3 Expand Rate", 1.0, 100.0, 1.0), kTypeOscExpandRate, parameters, osc3Params);
    addOscParameter(new FloatParameter("Osc 3 Phase", 0.0, kMaxPhase, 0.0), kTypeOscPhase, parameters, osc3Params);
    addOscParameter(new FloatParameter("Osc 3 Attack", kMinAdsr, kMaxAdsr, 0.05), kTypeOscAttack, parameters, osc3Params);
    addOscParameter(new FloatParameter("Osc 3 Attack Amp", 0.0, 1.0, 0.84), kTypeOscAttackAmp, parameters, osc3Params);
    addOscParameter(new FloatParameter("Osc 3 Decay", kMinAdsr, kMaxAdsr, 0.5), kTypeOscDecay, parameters, osc3Params);
    addOscParameter(new FloatParameter("Osc 3 Decay Amp", 0.0, 1.0, 0.475), kTypeOscDecayAmp, parameters, osc3Params);
    addOscParameter(new FloatParameter("Osc 3 Sustain", kMinAdsr, kMaxAdsr, 0.25), kTypeOscSustain, parameters, osc3Params);
    addOscParameter(new FloatParameter("Osc 3 Sustain Amp", 0.0, 1.0, 0.145), kTypeOscSustainAmp, parameters, osc3Params);
    addOscParameter(new FloatParameter("Osc 3 Release", kMinAdsr, kMaxAdsr, 0.5), kTypeOscRelease, parameters, osc3Params);
    addOscParameter(new DecibelParameter("Osc 3 Volume", -60.0, 0.0, 0.0), kTypeOscVolume, parameters, osc3Params);
    oscillators[2].observeParameters(osc1Params);

    parameters.add(new FloatParameter("Compressor Attack", 0.0, 10.0, 0.0));
    parameters.add(new FloatParameter("Compressor Release", 0.0, 50.0, 0.0));
    parameters.add(new FloatParameter("Compressor Ratio", 0.0, 3.0, 0.0));
    parameters.add(new DecibelParameter("Compressor Threshold", -30.0, 0.0, 0.0));

    parameters.add(new FrequencyParameter("Lopass Filter Frequency", 20.0, 10000.0, 10000.0));
    parameters.add(new FloatParameter("Lopass Filter Resonance", 0.1, sqrt(2.0), 1.0));

    parameters.add(new FloatParameter("Global Attack", kMinAdsr, kMaxAdsr, 0.05));
    parameters.add(new FloatParameter("Global Attack Amp", 0.0, 1.0, 0.84));
    parameters.add(new FloatParameter("Global Decay", kMinAdsr, kMaxAdsr, 0.5));
    parameters.add(new FloatParameter("Global Decay Amp", 0.0, 1.0, 0.475));
    parameters.add(new FloatParameter("Global Sustain", kMinAdsr, kMaxAdsr, 0.25));
    parameters.add(new FloatParameter("Global Sustain Amp", 0.0, 1.0, 0.145));
    parameters.add(new FloatParameter("Global Release", kMinAdsr, kMaxAdsr, 0.5));
    parameters.add(new DecibelParameter("Global Volume", -60.0, 0.0, 0.0));
}

KickMakerAudioProcessor::~KickMakerAudioProcessor()
{
}

//==============================================================================
void KickMakerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void KickMakerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void KickMakerAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < getNumInputChannels(); ++channel)
    {
        float* channelData = buffer.getSampleData (channel);

        // ..do something to the data...
    }

    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
}

//==============================================================================
AudioProcessorEditor* KickMakerAudioProcessor::createEditor()
{
    return new KickMakerAudioProcessorEditor (this);
}

//==============================================================================
void KickMakerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    XmlElement xml(getName());
    for (int i = 0; i < parameters.size(); i++) {
        PluginParameter *parameter = parameters[i];
        xml.setAttribute(parameter->getSafeName().c_str(), parameter->getValue());
    }
    copyXmlToBinary(xml, destData);
}

void KickMakerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != 0 && xmlState->hasTagName(getName())) {
        for (int i = 0; i < parameters.size(); i++) {
            PluginParameter *parameter = parameters[i];
            if (xmlState->hasAttribute(parameter->getSafeName().c_str())) {
                parameter->setValue(xmlState->getDoubleAttribute(parameter->getSafeName().c_str()));
            }
        }
        reset();
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KickMakerAudioProcessor();
}
