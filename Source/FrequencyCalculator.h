/*
  ==============================================================================

    FrequencyCalculator.h
    Created: 15 Mar 2013 10:27:10pm
    Author:  nik

  ==============================================================================
*/

#ifndef __FREQUENCYCALCULATOR_H_95E9AA40__
#define __FREQUENCYCALCULATOR_H_95E9AA40__

class FrequencyCalculator {
public:
    FrequencyCalculator();
    virtual ~FrequencyCalculator() {}

    float getFrequencyForNote(int note);

    void setDetune(float inDetune) { detune = inDetune; }
    void setDetuneFine(float inDetuneFine) { detuneFine = inDetuneFine; }

private:
    static float midiNoteFrequencies[128];

    float detune;
    float detuneFine;
    float expandAmount;
    float expandRate;
};

#endif  // __FREQUENCYCALCULATOR_H_95E9AA40__
