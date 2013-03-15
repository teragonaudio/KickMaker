/*
  ==============================================================================

    Compressor.h
    Created: 14 Mar 2013 9:55:40pm
    Author:  nik

  ==============================================================================
*/

#ifndef __COMPRESSOR_H_A61B1E37__
#define __COMPRESSOR_H_A61B1E37__

#include <math.h>
#include "../BufferProcessor.h"

class Compressor : public BufferProcessor {
public:
    Compressor() : BufferProcessor(), envDb(kDcOffset) {}
    virtual ~Compressor() {}

    void process(float* buffer, int numSamples);

    void setAttack(double inAttack) { attack = inAttack; calculateCoefficients(); }
    void setRelease(double inRelease) { release = inRelease; calculateCoefficients(); }
    void setThreshold(double inThreshold) { threshold = inThreshold; }
    void setRatio(double inRatio) { ratio = inRatio; }
    void setSampleRate(double inSampleRate) { sampleRate = inSampleRate; calculateCoefficients(); }

private:
    static const double kDcOffset = 1E-25;
    static double linear2dB(const double linear) {
        return log(linear) * 8.685889638; // 20 / lin(10)
    }
    static double db2linear(const double decibels) {
        return exp(decibels * 0.115129255); // ln(10) / 20
    }

    void calculateCoefficients();

private:
    double sampleRate;
    double envDb;

    float attack;
    float release;
    float threshold;
    float ratio;

    double attackCoefficient;
    double releaseCoefficient;
};

#endif  // __COMPRESSOR_H_A61B1E37__
