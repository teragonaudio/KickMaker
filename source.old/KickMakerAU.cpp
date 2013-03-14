/*
 *  KickMaker - KickMakerAU.cpp
 *  Created by Nik Reiman on 05.02.06
 *  Copyright (c) 2006 Teragon Audio, All rights reserved
 */

#ifndef __KickMakerAU_H
#include "KickMakerAU.h"
#endif

COMPONENT_ENTRY(KickMaker);

KickMaker::KickMaker(AudioUnit inInstance) :
MusicDeviceBase(inInstance, NUM_INPUTS, NUM_OUTPUTS, 0, 0) {
  init();
}

KickMaker::KickMaker(AudioUnit inInstance, UInt32 numInputElements, UInt32 numOutputElements,
                     UInt32 numGroupElements, UInt32 numPartElements) :
MusicDeviceBase(inInstance, numInputElements, numOutputElements,
                numGroupElements, numPartElements) {
  init();
}

AUChannelInfo KickMaker::m_channels[1] = { { 0, 2 } };

void KickMaker::init() {
  CreateElements();
	Globals()->UseIndexedParameters(NUM_PARAMS);
  
  core = new KickMakerCore(NUM_PARAMS, VERSION, DEF_PRODUCT);
  Float64 srate;
  if(DispatchGetProperty(kAudioUnitProperty_SampleRate, kAudioUnitScope_Global, 0, &srate) !=
     kAudioUnitErr_InvalidProperty) {
    core->setParameter(PRM_SAMPLE_RATE, srate, true);
  }
  
  editor = 0;
  
#if AU_DEBUG_DISPATCHER
	mDebugDispatcher = new AUDebugDispatcher(this);
#endif
}

KickMaker::~KickMaker() {
  delete core;
  
#if AU_DEBUG_DISPATCHER
  delete mDebugDispatcher;
#endif
}

int KickMaker::GetNumCustomUIComponents() {
  return 1;
}

ComponentResult KickMaker::GetParameter(AudioUnitParameterID inID,
                                        AudioUnitScope inScope,
                                        AudioUnitElement inElement,
                                        Float32 &outValue) {
  outValue = core->getParameter(REQ_VALUE, inID, NULL);
  return noErr;
}

ComponentResult	KickMaker::GetParameterInfo(AudioUnitScope inScope,
                                            AudioUnitParameterID inParameterID,
                                            AudioUnitParameterInfo &outParameterInfo) {
	ComponentResult result = noErr;
  
	outParameterInfo.flags = kAudioUnitParameterFlag_IsWritable
    |	kAudioUnitParameterFlag_IsReadable;
  
  if(inScope == kAudioUnitScope_Global) {
    char *c_name = new char[24];
    core->getParameter(REQ_NAME, inParameterID, c_name);
    CFStringRef name = CFStringCreateWithCString(kCFAllocatorDefault, c_name, 0);
    delete [] c_name;
    
    MusicDeviceBase::FillInParameterName(outParameterInfo, name, false);
    outParameterInfo.unit = (AudioUnitParameterUnit)core->getParameter(REQ_LABEL, inParameterID, NULL);
    outParameterInfo.minValue = core->getParameter(REQ_VALUE_MIN, inParameterID, NULL);
    outParameterInfo.maxValue = core->getParameter(REQ_VALUE_MAX, inParameterID, NULL);
    outParameterInfo.defaultValue = core->getParameter(REQ_VALUE_DEF, inParameterID, NULL);
	}
  else {
    result = MusicDeviceBase::GetParameterInfo(inScope, inParameterID, outParameterInfo);
  }
  
	return result;
}

ComponentResult	KickMaker::GetParameterValueStrings(AudioUnitScope inScope,
                                                    AudioUnitParameterID inParameterID,
                                                    CFArrayRef *outStrings) {
  return MusicDeviceBase::GetParameterValueStrings(inScope, inParameterID, outStrings);
}

ComponentResult KickMaker::GetProperty(AudioUnitPropertyID inID,
                                       AudioUnitScope inScope,
                                       AudioUnitElement inElement,
                                       void *outData) {
  if(inScope == kAudioUnitScope_Global) {
    switch(inID) {
      case PRP_CORE: {
        pluginCore **pc = (pluginCore**)outData;
        pc[0] = core;
        return noErr;
      }
      default:
        return MusicDeviceBase::GetProperty(inID, inScope, inElement, outData);
    }
  }
  return MusicDeviceBase::GetProperty(inID, inScope, inElement, outData);
}

ComponentResult KickMaker::GetPropertyInfo(AudioUnitPropertyID inID,
                                           AudioUnitScope inScope,
                                           AudioUnitElement inElement,
                                           UInt32& outDataSize,
                                           Boolean& outWritable) {
  if(inScope == kAudioUnitScope_Global) {
    switch(inID) {
      case PRP_CORE:
        outDataSize = sizeof(pluginCore*);
        return noErr;
      case PRP_EDITOR:
        outDataSize = sizeof(KickMakerEditor*);
        return noErr;
      default:
        return MusicDeviceBase::GetPropertyInfo(inID, inScope, inElement, outDataSize, outWritable);
    }
  }
  return MusicDeviceBase::GetPropertyInfo(inID, inScope, inElement, outDataSize, outWritable);
}

void KickMaker::GetUIComponentDescs(ComponentDescription* inDescArray) {
  inDescArray[0].componentType = kAudioUnitCarbonViewComponentType;
  inDescArray[0].componentSubType = KickMaker_COMP_SUBTYPE;
  inDescArray[0].componentManufacturer = KickMaker_COMP_MANF;
  inDescArray[0].componentFlags = 0;
  inDescArray[0].componentFlagsMask = 0;
}

OSStatus KickMaker::HandleMidiEvent(UInt8 inStatus,
                                    UInt8 inChannel,
                                    UInt8 inData1,
                                    UInt8 inData2,
                                    long inStartFrame) {
  core->processMidi(inStatus, inChannel, inData1, inData2, inStartFrame);
  return noErr;
}

ComponentResult KickMaker::GetPresets(CFArrayRef* outData) const {
  return -1;
}

ComponentResult	KickMaker::PrepareInstrument(MusicDeviceInstrumentID inInstrument) {
  return noErr;
}

ComponentResult	KickMaker::ReleaseInstrument(MusicDeviceInstrumentID inInstrument) {
  return noErr;
}

ComponentResult	KickMaker::Render(AudioUnitRenderActionFlags &ioActionFlags,
                                  const AudioTimeStamp &inTimeStamp,
                                  UInt32 inNumberFrames) {
  AudioBufferList &outBuffer = GetOutput(0)->GetBufferList();
  
  // Call the kernels to handle either interleaved or deinterleaved
	if(outBuffer.mNumberBuffers == 1) {
    m_outputs[0] = (float*)outBuffer.mBuffers[0].mData;
    m_outputs[1] = (float*)outBuffer.mBuffers[0].mData + 1;
	}
  else {
    m_outputs[0] = (float*)outBuffer.mBuffers[0].mData;
    m_outputs[1] = (float*)outBuffer.mBuffers[1].mData;
  }
  
  core->process(NULL, m_outputs, inNumberFrames);
  return noErr;
}

ComponentResult KickMaker::RestoreState(CFPropertyListRef inData) {
  ComponentResult result = MusicDeviceBase::RestoreState(inData);
  if(result != noErr) {
    return result;
  }

  CFDataRef cfdata = NULL;
  if(!CFDictionaryGetValueIfPresent((CFDictionaryRef)inData, CFSTR("PluginCore-data"), (const void**)&cfdata)) {
    return -1;
  }
  
  if(CFGetTypeID(cfdata) == CFDataGetTypeID()) {
    UInt8 *idata = const_cast<UInt8*>(CFDataGetBytePtr(cfdata));
    long datasize = CFDataGetLength(cfdata);
    core->setState(reinterpret_cast<unsigned char*>(idata), datasize);
  }
  
  return result;
}

ComponentResult KickMaker::SaveState(CFPropertyListRef *outData) {
  if(!outData) {
    return -1;
  }
  
  ComponentResult result = MusicDeviceBase::SaveState(outData);
  if(result != noErr) {
    return result;
  }
  
  int datasize = 0;
  UInt8 *idata = reinterpret_cast<UInt8*>(core->getState(datasize));
  if(datasize && idata) {
    CFDataRef cfdata = CFDataCreate(kCFAllocatorDefault, idata, (CFIndex)datasize);
    if(cfdata != NULL) {
      CFDictionarySetValue((CFMutableDictionaryRef)(*outData), CFSTR("PluginCore-data"), cfdata);
      CFRelease(cfdata);
    }
    else {
      result = -1;
    }
  }
  
  free(idata);
  return result;
}

ComponentResult KickMaker::SetParameter(AudioUnitParameterID inID,
                                        AudioUnitScope inScope,
                                        AudioUnitElement inElement,
                                        Float32 inValue,
                                        UInt32 inBufferOffsetInFrames) {
  core->setParameter(inID, inValue);
  
  if(editor) {
    ((KickMakerEditor*)editor)->updateControl(inID);
  }
  
  return AUBase::SetParameter(inID, inScope, inElement, inValue, inBufferOffsetInFrames);
}

ComponentResult KickMaker::SetProperty(AudioUnitPropertyID inID,
                                       AudioUnitScope inScope,
                                       AudioUnitElement inElement,
                                       const void *inData,
                                       UInt32 inDataSize) {
  if(inScope == kAudioUnitScope_Global) {
    switch(inID) {
      case PRP_EDITOR:
        editor = (KickMakerEditor*)inData;
        return noErr;
      default:
        return MusicDeviceBase::SetProperty(inID, inScope, inElement, inData, inDataSize);
    }
  }
  return MusicDeviceBase::SetProperty(inID, inScope, inElement, inData, inDataSize);
}

// This override is unused, as MIDI is handled by HandleMidiEvent()
// It is required, however, to inherit from the MusicDeviceBase class
ComponentResult KickMaker::StartNote(MusicDeviceInstrumentID inInstrument,
                                     MusicDeviceGroupID inGroupID,
                                     NoteInstanceID *outNoteInstanceID,
                                     UInt32 inOffsetSampleFrame,
                                     const MusicDeviceNoteParams &inParams) {
  return HandleMidiEvent(0x90, inGroupID, inParams.mPitch, inParams.mVelocity, inOffsetSampleFrame);
}

// This override is unused, as MIDI is handled by HandleMidiEvent()
// It is required, however, to inherit from the MusicDeviceBase class
ComponentResult KickMaker::StopNote(MusicDeviceGroupID inGroupID,
                                    NoteInstanceID inNoteInstanceID,
                                    UInt32 inOffsetSampleFrame) {
  return HandleMidiEvent(0x80, inGroupID, inNoteInstanceID, 0x00, inOffsetSampleFrame);
}

// Another required override from the MusicDeviceBase class
bool KickMaker::StreamFormatWritable(AudioUnitScope scope,
                                     AudioUnitElement element) {
  return true;
}

bool KickMaker::SupportsTail() {
  return false;
}

UInt32 KickMaker::SupportedNumChannels(const AUChannelInfo **outInfo) {
  if(outInfo != NULL) {
    *outInfo = &m_channels[0];
  }
  return 1;
  
}

ComponentResult KickMaker::Version() {
  return kKickMakerVersion;
}