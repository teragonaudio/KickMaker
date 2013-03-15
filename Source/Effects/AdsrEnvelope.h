/*
  ==============================================================================

    AdsrEnvelope.h
    Created: 14 Mar 2013 9:47:32pm
    Author:  nik

  ==============================================================================
*/

#ifndef __ADSRENVELOPE_H_73C34FE4__
#define __ADSRENVELOPE_H_73C34FE4__

#include "../BufferProcessor.h"

class AdsrEnvelope : public BufferProcessor {
public:
    AdsrEnvelope() {}
    virtual ~AdsrEnvelope() {}

    int getLength() const;
    void process(float* buffer, int numSamples);
    void resetIndex();

    void setSampleRate(double inSampleRate) { sampleRate = inSampleRate; calculateIndexes(); }

    void setAttack(float inAttack) { attack = inAttack; calculateIndexes(); }
    void setAttackAmp(float inAttackAmp) { attackAmp = inAttackAmp; calculateIndexes(); }
    void setDecay(float inDecay) { decay = inDecay; calculateIndexes(); }
    void setDecayAmp(float inDecayAmp) { decayAmp = inDecayAmp; calculateIndexes(); }
    void setSustain(float inSustain) { sustain = inSustain; calculateIndexes(); }
    void setSustainAmp(float inSustainAmp) { sustainAmp = inSustainAmp; calculateIndexes(); }
    void setRelease(float inRelease) { release = inRelease; calculateIndexes(); }

private:
    void calculateIndexes();

    double currentGain;
    long currentIndex;

    double sampleRate;
    float attack, attackAmp, decay, decayAmp, sustain, sustainAmp, release;
    double attackSlope, decaySlope, sustainSlope, releaseSlope;
    double attackIntercept, decayIntercept, sustainIntercept, releaseIntercept;
    long attackIndex, decayIndex, sustainIndex, releaseIndex;
};

#endif  // __ADSRENVELOPE_H_73C34FE4__
