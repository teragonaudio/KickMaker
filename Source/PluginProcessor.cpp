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
