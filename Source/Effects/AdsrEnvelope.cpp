/*
  ==============================================================================

    AdsrEnvelope.cpp
    Created: 14 Mar 2013 9:47:32pm
    Author:  nik

  ==============================================================================
*/

#include "AdsrEnvelope.h"

static const float kMaxSegmentLength = 0.25f;

int AdsrEnvelope::getLength() const
{
    return attackIndex + decayIndex + sustainIndex + releaseIndex;
}

void AdsrEnvelope::process(float* buffer, int numSamples)
{
    for(int i = 0; i < numSamples; ++i) {
        if(currentIndex < attackIndex) {
            buffer[i] *= (attackSlope * currentIndex++) + attackIntercept;
        }
        else if(currentIndex >= attackIndex && currentIndex < decayIndex) {
            buffer[i] *= (decaySlope * currentIndex++) + decayIntercept;
        }
        else if(currentIndex >= decayIndex && currentIndex < sustainIndex) {
            buffer[i] *= (sustainSlope * currentIndex++) + sustainIntercept;
        }
        else if(currentIndex >= sustainIndex && currentIndex < releaseIndex) {
            buffer[i] *= (releaseSlope * currentIndex++) + releaseIntercept;
        }
        else {
            buffer[i] = 0.0f;
            ++currentIndex;
        }
    }
}

void AdsrEnvelope::resetIndex()
{
    currentIndex = 0;
}

void AdsrEnvelope::calculateIndexes()
{
    float segmentSamples = kMaxSegmentLength * sampleRate;
    attackIndex = (long)(attack * segmentSamples);
    decayIndex = attackIndex + (long)(decay * segmentSamples);
    sustainIndex = decayIndex + (long)(sustain * segmentSamples);
    releaseIndex = sustainIndex + (long)(release * segmentSamples);

    attackSlope = attackAmp / attackIndex;
    decaySlope = (decayAmp - attackAmp) / (decayIndex - attackIndex);
    sustainSlope = (sustainAmp - decayAmp) / (sustainIndex - decayIndex);
    releaseSlope = (0.0f - sustainAmp) / (releaseIndex - sustainIndex);

    attackIntercept = 0.0f;
    decayIntercept = attackAmp - (decaySlope * attackIndex);
    sustainIntercept = decayAmp - (sustainSlope * decayIndex);
    releaseIntercept = sustainAmp - (releaseSlope * sustainIndex);
}
