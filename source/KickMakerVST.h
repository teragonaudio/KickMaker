/*
 *  KickMaker - KickMakerVST.h
 *  Created by Nik Reiman on 03.02.06
 *  Copyright (c) 2006 Teragon Audio, All rights reserved
 */

#ifndef __KickMakerVST_H
#define __KickMakerVST_H

#ifndef __KickMakerCore_H
#include "KickMakerCore.h"
#endif

#ifndef __audioeffectx__
#include "audioeffectx.h"
#endif

/////////////////////////////////////////////////////////////////////////

class KickMaker : public AudioEffectX {
  public:
    KickMaker(audioMasterCallback audioMaster);
    ~KickMaker();

    virtual VstInt32 canDo(char *text);
    virtual bool canParameterBeAutomated(VstInt32 index);
    virtual bool copyProgram(long destination);
    
    virtual VstInt32 getChunk(void **data, bool isPreset = false);
    virtual VstInt32 getCurrentMidiProgram(VstInt32 channel, MidiProgramName *currentProgram);
    virtual bool getEffectName(char *name);
    virtual bool getMidiKeyName(VstInt32 channel, MidiKeyName *keyName);
    virtual VstInt32 getMidiProgramCategory(VstInt32 channel, MidiProgramCategory *category);
    virtual VstInt32 getMidiProgramName(VstInt32 channel, MidiProgramName *midiProgramName);
    virtual VstInt32 getNumMidiInputChannels();
    virtual VstInt32 getNumMidiOutputChannels();
    virtual bool getOutputProperties(VstInt32 index, VstPinProperties *properties);
    virtual float getParameter(VstInt32 index);
    virtual void getParameterDisplay(VstInt32 index, char *text);
    virtual void getParameterLabel(VstInt32 index, char *label);
    virtual void getParameterName(VstInt32 index, char *text);
    virtual VstPlugCategory getPlugCategory();
    virtual VstInt32 getProgram();
    virtual void getProgramName(char *name);
    virtual bool getProgramNameIndexed(VstInt32 category, VstInt32 index, char *text);
    virtual bool getProductString(char *text);
    virtual bool getVendorString(char *text);
    virtual VstInt32 getVendorVersion();
    
    virtual bool hasMidiProgramsChanged(VstInt32 channel);

    virtual VstInt32 processEvents(VstEvents *events);
    virtual void process(float **inputs, float **outputs, VstInt32 sampleFrames);
    virtual void processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames);
    
    virtual void setBlockSize(VstInt32 blockSize);
    virtual VstInt32 setChunk(void *data, VstInt32 byteSize, bool isPreset = false);
    virtual void setSampleRate(float sampleRate);
    virtual void setParameter(VstInt32 index, float value);
    virtual void setParameterAutomated(VstInt32 index, float value);
    virtual void setProgram(VstInt32 index);
    virtual void setProgramName(char *name);  
  
protected:

  private:
    void fillProgram(VstInt32 channel, VstInt32 prg, MidiProgramName* mpn);
    void initProcess();

    KickMakerCore *core;
};

#endif
