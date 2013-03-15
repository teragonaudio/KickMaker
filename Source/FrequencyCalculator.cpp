/*
  ==============================================================================

    FrequencyCalculator.cpp
    Created: 15 Mar 2013 10:27:10pm
    Author:  nik

  ==============================================================================
*/

#include "FrequencyCalculator.h"

FrequencyCalculator::FrequencyCalculator()
{
    float step = 1.059463094359f; // 12th root of 2
    // Assume we are being passed in something close to A4, so this must be converted to C2,
    // which is MIDI note number 0
    float base = 440.0f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * step * step * step;
    for(int i = 0; i < 128; ++i) {
        midiNoteFrequencies[i] = base;
        base *= step;
    }
}

float FrequencyCalculator::getFrequencyForNote(int note)
{
}
