/*
 *  auLoader.cpp - pluginCore
 *
 *  Created by Nik Reiman on 04.01.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 *  This source code may NOT be redistributed without express permission of Teragon Audio.  It may be used
 *  in free or commercial software works, but unauthorized duplication or resale in whole or part is
 *  strictly prohibited.
 */

#if USE_PC_AU
#if USE_PC_HOST

#ifndef __auLoader_H
#include "auLoader.h"
#endif

/*! \brief AU properties */
static UInt32 _AUCODES[] =
{
  // Applicable to all AudioUnits in general (0 -> 999)
	kAudioUnitProperty_ClassInfo,
	kAudioUnitProperty_MakeConnection,
	kAudioUnitProperty_SampleRate,
	kAudioUnitProperty_ParameterList,
	kAudioUnitProperty_ParameterInfo,
	kAudioUnitProperty_FastDispatch,
	kAudioUnitProperty_CPULoad,
	
  //kAudioUnitProperty_SetInputCallback = 7 -> deprecated - see AUNTComponent.h
	kAudioUnitProperty_StreamFormat,
	kAudioUnitProperty_SRCAlgorithm,
	kAudioUnitProperty_ReverbRoomType,
	kAudioUnitProperty_BusCount,
	kAudioUnitProperty_ElementCount,
	kAudioUnitProperty_Latency,
	kAudioUnitProperty_SupportedNumChannels,
	kAudioUnitProperty_MaximumFramesPerSlice,
	kAudioUnitProperty_SetExternalBuffer,
	kAudioUnitProperty_ParameterValueStrings,
	kAudioUnitProperty_MIDIControlMapping, // deprecated see ParameterMIDIMapping Properties
	kAudioUnitProperty_GetUIComponentList,
	kAudioUnitProperty_AudioChannelLayout,  
	kAudioUnitProperty_TailTime,
	kAudioUnitProperty_BypassEffect,
	kAudioUnitProperty_LastRenderError,
	kAudioUnitProperty_SetRenderCallback,
	kAudioUnitProperty_FactoryPresets,
	kAudioUnitProperty_ContextName,
	kAudioUnitProperty_RenderQuality,
	kAudioUnitProperty_HostCallbacks,
	kAudioUnitProperty_CurrentPreset,
	kAudioUnitProperty_InPlaceProcessing,
	kAudioUnitProperty_ElementName,
	kAudioUnitProperty_CocoaUI,
	kAudioUnitProperty_SupportedChannelLayoutTags,
	kAudioUnitProperty_ParameterValueName,
	kAudioUnitProperty_ParameterIDName,
	kAudioUnitProperty_ParameterClumpName,
	kAudioUnitProperty_PresentPreset,
	kAudioUnitProperty_UsesInternalReverb,
	kAudioUnitProperty_OfflineRender,
	kAudioUnitProperty_ParameterValueName, // Is the same as kAudioUnitProperty_ParameterStringFromValue
	// This is the new property to retrieve the actual parameter value from a parameter name
	kAudioUnitProperty_ParameterValueFromString,
	kAudioUnitProperty_IconLocation,
	kAudioUnitProperty_PresentationLatency,
	kAudioUnitProperty_AllParameterMIDIMappings,
	kAudioUnitProperty_AddParameterMIDIMapping,
	kAudioUnitProperty_RemoveParameterMIDIMapping,
	kAudioUnitProperty_HotMapParameterMIDIMapping,
	kAudioUnitProperty_DependentParameters,
	
  // Applicable to MusicDevices (1000 -> 1999)
	kMusicDeviceProperty_InstrumentCount,
	kMusicDeviceProperty_InstrumentName,
	kMusicDeviceProperty_GroupOutputBus,
	kMusicDeviceProperty_SoundBankFSSpec,
	kMusicDeviceProperty_InstrumentNumber,
	kAudioUnitProperty_UsesInternalReverb, // Is the same as kMusicDeviceProperty_UsesInternalReverb
	kMusicDeviceProperty_MIDIXMLNames,
	kMusicDeviceProperty_BankName,
	kMusicDeviceProperty_SoundBankData,
	kMusicDeviceProperty_PartGroup,
	kMusicDeviceProperty_StreamFromDisk,
	kMusicDeviceProperty_SoundBankFSRef,
	
  // Applicable to "output" AudioUnits (2000 -> 2999)
	kAudioOutputUnitProperty_CurrentDevice,
	kAudioOutputUnitProperty_IsRunning,
	kAudioOutputUnitProperty_ChannelMap, // this will also work with AUConverter
	kAudioOutputUnitProperty_EnableIO,
	kAudioOutputUnitProperty_StartTime,
	kAudioOutputUnitProperty_SetInputCallback,
	kAudioOutputUnitProperty_HasIO,
	kAudioOutputUnitProperty_StartTimestampsAtZero, // this will also work with AUConverter
  
  // Miscellaneous AudioUnit - specific properties
	kAudioUnitProperty_SpatializationAlgorithm,
	kAudioUnitProperty_SpeakerConfiguration,
	kAudioUnitProperty_DopplerShift,
	kAudioUnitProperty_3DMixerRenderingFlags,
	kAudioUnitProperty_3DMixerDistanceAtten,
	kAudioUnitProperty_MatrixLevels,
	kAudioUnitProperty_MeteringMode,
	kAudioUnitProperty_PannerMode,
	kAudioUnitProperty_MatrixDimensions,
	kAudioUnitProperty_3DMixerDistanceParams,
	kAudioUnitProperty_MeterClipping, // matrix mixer returns an AudioUnitMeterClipping struct
  
  // Offline unit properties
	kAudioOfflineUnitProperty_InputSize,
	kAudioOfflineUnitProperty_OutputSize,
	kAudioUnitOfflineProperty_StartOffset,
	kAudioUnitOfflineProperty_PreflightRequirements,
	kAudioUnitOfflineProperty_PreflightName,
  
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
	// For AUScheduledSoundPlayer:
  kAudioUnitProperty_ScheduleAudioSlice, // ScheduledAudioSlice
	kAudioUnitProperty_ScheduleStartTimeStamp, // AudioTimeStamp, with either sample time or host time valid.
	kAudioUnitProperty_CurrentPlayTime, // AudioTimeStamp, relative to start time, sample time of -1 if not yet started.
#endif
};

extern "C"
{
  /*! \brief Returns a string description for a given property */
  static char* AUPropertyStr(AudioUnitPropertyID inID)
  {
    switch (inID)
    {
      case kAudioUnitProperty_ClassInfo: return "Class Info";
      case kAudioUnitProperty_MakeConnection: return "Connection";
      case kAudioUnitProperty_SampleRate: return "Sample Rate";
      case kAudioUnitProperty_ParameterList: return "Parameter List";
      case kAudioUnitProperty_ParameterInfo: return "Parameter Info";
      case kAudioUnitProperty_FastDispatch: return "Fast Dispatch";
      case kAudioUnitProperty_CPULoad: return "CPU Load";
      case kAudioUnitProperty_StreamFormat: return "Format";
      case kAudioUnitProperty_SRCAlgorithm: return "SRC Algo";
      case kAudioUnitProperty_ReverbRoomType: return "Reverb Room Type";
      case kAudioUnitProperty_BusCount: return "Bus Count";
      case kAudioUnitProperty_Latency: return "Latency";
      case kAudioUnitProperty_SupportedNumChannels: return "Supported Num Channels";
      case kAudioUnitProperty_MaximumFramesPerSlice: return "Max Frames Per Slice";
      case kAudioUnitProperty_SetExternalBuffer: return "Set External Buffer";
      case kAudioUnitProperty_ParameterValueStrings: return "Parameter Value Strings";
      case kAudioUnitProperty_MIDIControlMapping: return "MIDI Control Mapping";
      case kAudioUnitProperty_GetUIComponentList: return "Carbon UI";
      case kAudioUnitProperty_AudioChannelLayout: return "Audio Channel Layout";  
      case kAudioUnitProperty_TailTime: return "Tail Time";
      case kAudioUnitProperty_BypassEffect: return "Bypass Effect";
      case kAudioUnitProperty_LastRenderError: return "Last Render Error";
      case kAudioUnitProperty_SetRenderCallback: return "Render Callback";
      case kAudioUnitProperty_FactoryPresets: return "Factory Preset";
      case kAudioUnitProperty_ContextName: return "Context Name";
      case kAudioUnitProperty_RenderQuality: return "Render Quality";
      case kAudioUnitProperty_HostCallbacks: return "Host Callbacks";
      case kAudioUnitProperty_CurrentPreset: return "Current Preset";
      case kAudioUnitProperty_InPlaceProcessing: return "In Place Processing";
      case kAudioUnitProperty_ElementName: return "Element Name";
      case kAudioUnitProperty_CocoaUI: return "Cocoa UI";
      case kAudioUnitProperty_SupportedChannelLayoutTags: return "Supported Channel Layout Tags";
      case kAudioUnitProperty_ParameterValueName: return "Parameter Value Name";
      case kAudioUnitProperty_UsesInternalReverb: return "Use Internal Reverb";
      case kAudioUnitProperty_ParameterIDName: return "Parameter ID Name";
      case kAudioUnitProperty_ParameterClumpName: return "Clump Name";
      case kAudioUnitProperty_PresentPreset: return "Present Preset";

      case kMusicDeviceProperty_InstrumentCount: return "Instrument Count";
      case kMusicDeviceProperty_InstrumentName: return "Instrument Name";
      case kMusicDeviceProperty_GroupOutputBus: return "Group Output Bus";
      case kMusicDeviceProperty_SoundBankFSSpec: return "Sound Bank - File";
      case kMusicDeviceProperty_InstrumentNumber: return "Instrument Number";
      case kMusicDeviceProperty_MIDIXMLNames: return "MIDI XML Names";
      case kMusicDeviceProperty_BankName: return "Bank Name";
      case kMusicDeviceProperty_SoundBankData: return "Sound Bank - Data";

      case kAudioOutputUnitProperty_CurrentDevice: return "Current AudioDevice";
      case kAudioOutputUnitProperty_IsRunning: return "Is Running";
      case kAudioOutputUnitProperty_ChannelMap: return "Channel Map";
      case kAudioOutputUnitProperty_EnableIO: return "Enable I/O";
      case kAudioOutputUnitProperty_StartTime: return "Start Time";
      case kAudioOutputUnitProperty_SetInputCallback: return "I/O Input Callback";
    }
    return "Unknown";
  }
}

/*! Unfortunately, a global variable is needed to properly coordinate exchange of data between
* plugin and host.  This is because AU is designed to be a "pull" protocol instead of a "push"
* protocol.
* \todo This may not be thread-safe.
*/
float **_INPUTS;

auLoader::auLoader()
{
  m_buffer_list = 0;
  _INPUTS = new float*[MAX_CHANNELS];
  for(int i = 0; i < MAX_CHANNELS; ++i)
  {
    _INPUTS[i] = 0;
  }
  m_time.mSampleTime = 0;
  m_time.mFlags = kAudioTimeStampSampleTimeValid;
}

auLoader::~auLoader()
{
  if(m_plugin)
  {
    CloseComponent(m_plugin);
  }
  if(m_buffer_list)
  {
    free(m_buffer_list);
  }
  for(int i = 0; i < MAX_CHANNELS; ++i)
  {
    if(_INPUTS[i])
    {
      delete [] _INPUTS[i];
    }
  }
  delete [] _INPUTS;
}

void* auLoader::getPluginPtr() const
{
  return NULL;
}

bool auLoader::initialize()
{
  /** Algorithm: **/
  /** Call the AU's Initialize method **/
  OSStatus err = AudioUnitInitialize(m_plugin);
  if(err != noErr)
  {
    debug(LOG_ERROR, "Could not initialize plugin");
    return false;
  }
  
  /** Set up output buffers **/
  m_buffer_list = (AudioBufferList *)malloc(offsetof(AudioBufferList, mBuffers[MAX_CHANNELS]));
  m_buffer_list->mNumberBuffers = MAX_CHANNELS;
  
  /** Connect input properties **/
  AURenderCallbackStruct callback;
  callback.inputProc = this->inputCallback;
  callback.inputProcRefCon = this;
  
  /** Set up render notifications **/
  err = AudioUnitSetProperty(m_plugin, kAudioUnitProperty_SetRenderCallback, kAudioUnitScope_Input,
                             0, &callback, sizeof(callback));
  if(err != noErr)
  {
    debug(LOG_WARN, "Could not configure inputs");
  }
  
  err = AudioUnitAddRenderNotify(m_plugin, this->renderNotify, NULL);
  if(err != noErr)
  {
    debug(LOG_ERROR, "Could not set up render notification");
  }
  
  debug(LOG_INFO, "AU initialized");
  return true;
}

OSStatus auLoader::inputCallback(void *inRefCon,
                                 AudioUnitRenderActionFlags *ioActionFlags,
                                 const AudioTimeStamp *inTimeStamp,
                                 UInt32 inBusNumber,
                                 UInt32 inNumFrames,
                                 AudioBufferList *ioData)
{
  debug(LOG_VERBOSE, "Input requested from plugin for bus %d", inBusNumber);
  for(int i = 0; i < ioData->mNumberBuffers; ++i)
  {
    memcpy(ioData->mBuffers[i].mData, _INPUTS[i], ioData->mBuffers[i].mDataByteSize);
  }
  return noErr;
}

bool auLoader::loadPlugin()
{
  Component comp = FindNextComponent(NULL, &m_desc);
  if(comp == NULL)
  {
    debug(LOG_ERROR, "AU '%s' '%s' '%s' was not found", m_type, m_subtype, m_manuf);
    return false;
  }
  else
  {
    debug(LOG_INFO, "AU '%s' '%s' '%s' found", m_type, m_subtype, m_manuf);
  }
  
  OSErr result = OpenAComponent(comp, &m_plugin);
  if(result)
  {
    debug(LOG_ERROR, "Could not open AU");
    return false;
  }
  else
  {
    debug(LOG_INFO, "AU opened");
  }
  
  return true;
}

void auLoader::printInfo() const
{
  UInt32 size;
  void *data;
  Boolean write;
  ComponentResult err = noErr;
  
  debug(LOG_INFO, "Plugin Properties:");
  for(int i = 0; i < sizeof(_AUCODES) / sizeof(UInt32); ++i) {
    data = 0;
    err = AudioUnitGetPropertyInfo(m_plugin, _AUCODES[i], kAudioUnitScope_Global, 0, &size, &write);
    if(size && err == noErr) {
      if(write) {
        debug(LOG_INFO, "  %s: %d bytes (+ writeable)", AUPropertyStr(_AUCODES[i]), size);
      }
      else {
        debug(LOG_INFO, "  %s: %d bytes", AUPropertyStr(_AUCODES[i]), size);
      }
    }
    
    if(data) {
      free(data);
    }
  }
  
  // Get parameter information
  AudioUnitParameterInfo auinfo;
  UInt32 *plist;
  int num_params = 0;
  err = AudioUnitGetPropertyInfo(m_plugin, kAudioUnitProperty_ParameterList, kAudioUnitScope_Global, 0, &size, &write);
  if(err == noErr && size > 0) {
    num_params = size / sizeof(UInt32);
    plist = new UInt32[num_params];
    err = AudioUnitGetProperty(m_plugin, kAudioUnitProperty_ParameterList, kAudioUnitScope_Global, 0, plist, &size);
  }
  
  debug(LOG_INFO, "Parameters (%d total):", num_params);
  for(int i = 0; i < num_params; ++i) {
    err = AudioUnitGetPropertyInfo(m_plugin, kAudioUnitProperty_ParameterInfo, kAudioUnitScope_Global, plist[i], &size, &write);
    if(size == sizeof(AudioUnitParameterInfo) && err == noErr) {
      err = AudioUnitGetProperty(m_plugin, kAudioUnitProperty_ParameterInfo, kAudioUnitScope_Global, plist[i], &auinfo, &size);
      if(err == noErr) {
        debug(LOG_INFO, "  %d: %s, type %d, min %f, max %f", plist[i], auinfo.name, auinfo.unit, auinfo.minValue, auinfo.maxValue);
      }
    }
  }
}

void auLoader::process(float **inputs, float **outputs, long frames) {  
  for(int i = 0; i < MAX_CHANNELS; ++i) {
    m_buffer_list->mBuffers[i].mNumberChannels = 1;
    m_buffer_list->mBuffers[i].mDataByteSize = frames * sizeof(Float32);
    m_buffer_list->mBuffers[i].mData = outputs[i];
    memset(m_buffer_list->mBuffers[i].mData, 0x0, m_buffer_list->mBuffers[i].mDataByteSize);
  
    memcpy(_INPUTS[i], inputs[i], sizeof(float) * frames);
  }

  AudioUnitRenderActionFlags flags = 0;
  OSStatus err = AudioUnitRender(m_plugin, &flags, &m_time, 0, frames, m_buffer_list);
  if(err != noErr) {
    debug(LOG_ERROR, "Render failed with code %d", err);
  }
  else {
    debug(LOG_VERBOSE, "Render complete");
  }
  
  m_time.mSampleTime += frames;
}

void auLoader::processMidi(int type, int byte1, int byte2, long frames) {
  if(m_desc.componentType == kAudioUnitType_MusicDevice ||
     m_desc.componentType == kAudioUnitType_MusicEffect) {
    MusicDeviceMIDIEvent(m_plugin, type, byte1, byte2, frames);
  }
}

void auLoader::resume() {
/*! \todo Do AU's need to actually do anything here? */
}

OSStatus auLoader::renderNotify(void *inRefCon, 
                                AudioUnitRenderActionFlags *ioActionFlags,
                                const AudioTimeStamp *inTimeStamp, 
                                UInt32 inBusNumber,
                                UInt32 inNumFrames, 
                                AudioBufferList *ioData) {
  if(*ioActionFlags & kAudioUnitRenderAction_PreRender) {
    debug(LOG_VERBOSE, "Pre render cycle for bus %d", inBusNumber);
    return noErr;
  }
  if(*ioActionFlags & kAudioUnitRenderAction_PostRender) {
    debug(LOG_VERBOSE, "Post render cycle for bus %d", inBusNumber);
    return noErr;
  }
  return noErr;
}

bool auLoader::setBlocksize(int bsize) {
  for(int i = 0; i < MAX_CHANNELS; ++i) {
    if(_INPUTS[i]) {
      delete [] _INPUTS[i];
    }
    _INPUTS[i] = new float[bsize];
  }
  return true;
}

bool auLoader::setParameter(int index, float value, long frames) {
  if(AudioUnitSetParameter(m_plugin, index, kAudioUnitScope_Global, 0, value, frames) == noErr) {
    return true;
  }
  else {
    return false;
  }
}

bool auLoader::setPath(const char *fname) {
  // Assume we are being passed a colon-delimited string in the form TYPE:SUBTYPE:MANUF
  char *colon = strchr(fname, ':');
  if(colon != NULL) {
    strncpy(m_type, fname, 4);
    m_type[4] = '\0';
  }
  else {
    return false;
  }
  
  colon = strchr(colon + 1, ':');
  if(colon != NULL) {
    strncpy(m_subtype, fname + 5, 4);
    m_subtype[4] = '\0';
    strncpy(m_manuf, fname + 10, 4);
    m_manuf[4] = '\0';
  }
  else {
    return false;
  }
  
  m_desc.componentType = m_type[0];
  m_desc.componentType <<= 8;
  m_desc.componentType += m_type[1];
  m_desc.componentType <<= 8;
  m_desc.componentType += m_type[2];
  m_desc.componentType <<= 8;
  m_desc.componentType += m_type[3];
    
  m_desc.componentSubType = m_subtype[0];
  m_desc.componentSubType <<= 8;
  m_desc.componentSubType += m_subtype[1];
  m_desc.componentSubType <<= 8;
  m_desc.componentSubType += m_subtype[2];
  m_desc.componentSubType <<= 8;
  m_desc.componentSubType += m_subtype[3];
    
  m_desc.componentManufacturer = m_manuf[0];
  m_desc.componentManufacturer <<= 8;
  m_desc.componentManufacturer += m_manuf[1];
  m_desc.componentManufacturer <<= 8;
  m_desc.componentManufacturer += m_manuf[2];
  m_desc.componentManufacturer <<= 8;
  m_desc.componentManufacturer += m_manuf[3];
  
  m_desc.componentFlags = 0;
  m_desc.componentFlagsMask = 0;
  
  return true;
}

bool auLoader::setProgram(int num) {
  /*! \todo Does AU even support this? */
  return true;
}

bool auLoader::setSampleRate(float srate) {
  UInt32 size;
  Boolean write;
  Float64 data = srate;
  ComponentResult err = AudioUnitGetPropertyInfo(m_plugin, kAudioUnitProperty_SampleRate, kAudioUnitScope_Global, 0, &size, &write);
  if(err == noErr && size == sizeof(Float64)) {
    err = AudioUnitSetProperty(m_plugin, kAudioUnitProperty_SampleRate, kAudioUnitScope_Global, 0, &data, size);
    if(err != noErr) {
      debug(LOG_ERROR, "Could not set sample rate to %f", srate);
      return false;
    }
    else {
      debug(LOG_VERBOSE, "Set sample rate to %f", srate);
    }
  }
  
  if(m_desc.componentType == kAudioUnitType_Effect ||
     m_desc.componentType == kAudioUnitType_MusicEffect) {
    AudioStreamBasicDescription stream_format;
    stream_format.mSampleRate = srate;
    stream_format.mFormatID = kAudioFormatLinearPCM;
    stream_format.mFormatFlags = kAudioFormatFlagsNativeFloatPacked | kAudioFormatFlagIsNonInterleaved;
    stream_format.mBytesPerPacket = 4;
    stream_format.mFramesPerPacket = 1;
    stream_format.mBytesPerFrame = 4;
    stream_format.mChannelsPerFrame = MAX_CHANNELS;
    stream_format.mBitsPerChannel = sizeof(Float32) * 8;
    
    err = AudioUnitSetProperty(m_plugin, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input,
                               0, &stream_format, sizeof(stream_format));
    if(err != noErr) {
      debug(LOG_ERROR, "Could not set stream format");
      return false;
    }
    else {
      debug(LOG_VERBOSE, "Set stream format");
    }
  }
  
  return true;
}

void auLoader::suspend() {
  /*! \todo Does AU support this? */
}

#endif
#endif