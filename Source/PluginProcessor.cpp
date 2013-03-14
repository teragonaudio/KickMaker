/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
KickMakerAudioProcessor::KickMakerAudioProcessor()
{
}

KickMakerAudioProcessor::~KickMakerAudioProcessor()
{
}

//==============================================================================
const String KickMakerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int KickMakerAudioProcessor::getNumParameters()
{
    return 0;
}

float KickMakerAudioProcessor::getParameter (int index)
{
    return 0.0f;
}

void KickMakerAudioProcessor::setParameter (int index, float newValue)
{
}

const String KickMakerAudioProcessor::getParameterName (int index)
{
    return String::empty;
}

const String KickMakerAudioProcessor::getParameterText (int index)
{
    return String::empty;
}

const String KickMakerAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String KickMakerAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool KickMakerAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool KickMakerAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool KickMakerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool KickMakerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool KickMakerAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double KickMakerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int KickMakerAudioProcessor::getNumPrograms()
{
    return 0;
}

int KickMakerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void KickMakerAudioProcessor::setCurrentProgram (int index)
{
}

const String KickMakerAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void KickMakerAudioProcessor::changeProgramName (int index, const String& newName)
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
bool KickMakerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* KickMakerAudioProcessor::createEditor()
{
    return new KickMakerAudioProcessorEditor (this);
}

//==============================================================================
void KickMakerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void KickMakerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KickMakerAudioProcessor();
}
