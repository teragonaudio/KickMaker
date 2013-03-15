/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef __PLUGINPROCESSOR_H_C7A4E721__
#define __PLUGINPROCESSOR_H_C7A4E721__

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"
#include "PluginParameters.h"

using namespace teragon;

//==============================================================================
class KickMakerAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    KickMakerAudioProcessor();
    ~KickMakerAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

    //==============================================================================
    AudioProcessorEditor* createEditor();
    bool hasEditor() const { return true; }

    //==============================================================================
    const String getName() const { return JucePlugin_Name; }

    int getNumParameters() { return parameters.size(); }
    float getParameter (int index) { return parameters[index]->getScaledValue(); }
    void setParameter (int index, float newValue) { parameters[index]->setScaledValue(newValue); }

    const String getParameterName (int index) { return parameters[index]->getName().c_str(); }
    const String getParameterText (int index) { return parameters[index]->getDisplayText().c_str(); }

    const String getInputChannelName (int channelIndex) const { return String(channelIndex + 1); }
    const String getOutputChannelName (int channelIndex) const { return String(channelIndex + 1); }
    bool isInputChannelStereoPair (int index) const { return true; }
    bool isOutputChannelStereoPair (int index) const { return true; }

    bool acceptsMidi() const { return true; }
    bool producesMidi() const { return false; }
    bool silenceInProducesSilenceOut() const { return true; }
    double getTailLengthSeconds() const { return 0.0; }

    //==============================================================================
    int getNumPrograms() { return 0; }
    int getCurrentProgram() { return 0; }
    void setCurrentProgram (int index) {}
    const String getProgramName (int index) { return String::empty; }
    void changeProgramName (int index, const String& newName) {}

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

private:
    PluginParameterSet parameters;
    Oscillator oscillators[3];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KickMakerAudioProcessor)
};

#endif  // __PLUGINPROCESSOR_H_C7A4E721__
