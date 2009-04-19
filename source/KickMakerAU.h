/*
 *  KickMaker - KickMakerAU.h
 *  Created by Nik Reiman on 05.02.06
 *  Copyright (c) 2006 Teragon Audio, All rights reserved
 */

#ifndef __KickMakerAU_H
#define __KickMakerAU_H

#ifndef __defaults_H
#include "defaults.h"
#endif

#ifndef __KickMakerCore_H
#include "KickMakerCore.h"
#endif

#ifndef __KickMakerEditor_H
#include "KickMakerEditor.h"
#endif

#include "AUCarbonViewBase.h"
#include "AUCarbonViewControl.h"
#include "MusicDeviceBase.h"

#if AU_DEBUG_DISPATCHER
#include "AUDebugDispatcher.h"
#endif

class KickMaker : public MusicDeviceBase {
  public:
    KickMaker(AudioUnit inInstance);
    KickMaker(AudioUnit inInstance, UInt32 numInputElements, UInt32 numOutputElements,
              UInt32 numGroupElements, UInt32 numPartElements);
    virtual ~KickMaker();
    
    virtual int GetNumCustomUIComponents();
    virtual	ComponentResult GetParameterValueStrings(AudioUnitScope inScope,
                                                     AudioUnitParameterID inParameterID,
                                                     CFArrayRef *outStrings);
    virtual ComponentResult GetParameter(AudioUnitParameterID inID,
                                         AudioUnitScope inScope,
                                         AudioUnitElement inElement,
                                         Float32 &outValue);
    virtual	ComponentResult GetParameterInfo(AudioUnitScope inScope,
                                             AudioUnitParameterID	inParameterID,
                                             AudioUnitParameterInfo	&outParameterInfo);
    virtual ComponentResult GetPresets(CFArrayRef* outData) const;
    virtual ComponentResult GetProperty(AudioUnitPropertyID inID,
                                        AudioUnitScope inScope,
                                        AudioUnitElement inElement,
                                        void *outData);
    virtual ComponentResult GetPropertyInfo(AudioUnitPropertyID inID,
                                            AudioUnitScope inScope,
                                            AudioUnitElement inElement,
                                            UInt32 &outDataSize,
                                            Boolean &outWritable);
    virtual void GetUIComponentDescs(ComponentDescription* inDescArray);
    virtual OSStatus HandleMidiEvent(UInt8 inStatus,
                                     UInt8 inChannel,
                                     UInt8 inData1,
                                     UInt8 inData2,
                                     long inStartFrame);
    virtual ComponentResult	PrepareInstrument(MusicDeviceInstrumentID inInstrument);
    virtual ComponentResult	ReleaseInstrument(MusicDeviceInstrumentID inInstrument);
    virtual ComponentResult Render(AudioUnitRenderActionFlags &ioActionFlags,
                                   const AudioTimeStamp &inTimeStamp,
                                   UInt32 inNumberFrames);
    virtual ComponentResult RestoreState(CFPropertyListRef inData);
    virtual ComponentResult SaveState(CFPropertyListRef* outData);
    virtual ComponentResult SetParameter(AudioUnitParameterID inID,
                                         AudioUnitScope inScope,
                                         AudioUnitElement inElement,
                                         Float32 inValue,
                                         UInt32 inBufferOffsetInFrames);
    virtual ComponentResult SetProperty(AudioUnitPropertyID inID,
                                        AudioUnitScope inScope,
                                        AudioUnitElement inElement,
                                        const void *inData,
                                        UInt32 inDataSize);
    virtual ComponentResult StartNote(MusicDeviceInstrumentID inInstrument,
                                      MusicDeviceGroupID inGroupID,
                                      NoteInstanceID *outNoteInstanceID,
                                      UInt32 inOffsetSampleFrame,
                                      const MusicDeviceNoteParams &inParams);
    virtual ComponentResult StopNote(MusicDeviceGroupID inGroupID,
                                     NoteInstanceID inNoteInstanceID,
                                     UInt32 inOffsetSampleFrame);
    virtual bool StreamFormatWritable(AudioUnitScope scope,
                                      AudioUnitElement element);
    virtual UInt32 SupportedNumChannels(const AUChannelInfo **outInfo);
    virtual	bool SupportsTail();
    virtual ComponentResult	Version();
        
  protected:
  private:
    void init();
    
    KickMakerCore *core;
    KickMakerEditor *editor;
    static AUChannelInfo m_channels[1];
    float *m_outputs[NUM_OUTPUTS];
};

#endif