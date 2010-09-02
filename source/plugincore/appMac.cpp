/*
 *  appMac.cpp - pluginCore
 *
 *  Created by Nik Reiman on 12.11.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 *  This source code may NOT be redistributed without express permission of Teragon Audio.  It may be used
 *  in free or commercial software works, but unauthorized duplication or resale in whole or part is
 *  strictly prohibited.
 *
 *  STILL UNDER DEVELOPMENT - USE WITH CAUTION
 *
 */

#ifdef USE_PC_APP
#if MAC

#ifndef __appMac_H
#include "appMac.h"
#endif

VstTimeInfo _TIME;

int main(int argc, char *argv[]) {
  OSStatus err = noErr;
  
  // Set up signaling stuff first
  signal(SIGHUP, &quit);
  signal(SIGINT, &quit);
  signal(SIGILL, &quit);
  signal(SIGTRAP, &quit);
  signal(SIGABRT, &quit);
  signal(SIGEMT, &quit);
  signal(SIGFPE, &quit);
  signal(SIGBUS, &quit);
  signal(SIGSEGV, &quit);
  signal(SIGPIPE, &quit);
  signal(SIGALRM, &quit);
  signal(SIGTERM, &quit);
  signal(SIGURG, &quit);
  
  char path[MAX_PATH], tmp[MAX_PATH];
  if(getPluginBundleDir(DEF_BUNDLE_STRING, tmp)) {
    snprintf(path, MAX_PATH, "%s%c%s%c%s%s", tmp, DEF_DELIMITER, DEF_RESOURCE_PATH,
             DEF_DELIMITER, DEF_PRODUCT, DEF_EXTENSION);
  }
  
#if USE_PC_MIDI
  /*
   MIDIClientRef mc;
   if(MIDIClientCreate(CFSTR(DEF_PRODUCT), NULL, NULL, &mc) != noErr) {
     printf("Could not initialize MIDI subsystem\n");
   }
   printf("%d extern devices, %d devs\n", MIDIGetNumberOfDevices());
   for(int i = 0; i < MIDIGetNumberOfDevices(); ++i) {
     MIDIDeviceRef dev = MIDIGetDevice(i);
     printf("Device %d has %d entities\n", i, MIDIDeviceGetNumberOfEntities(dev));
     for(int j = 0; j < MIDIDeviceGetNumberOfEntities(dev); ++j) {
       MIDIEntityRef entity = MIDIDeviceGetEntity(dev, j);
       CFPropertyListRef props;
       MIDIObjectGetProperties(entity, &props, true);
       printf("Entity has %d prop keys\n", CFDictionaryGetCount((CFDictionaryRef)props));
       int size = CFDictionaryGetCount((CFDictionaryRef)props);
       const void **keys = (const void **)malloc (sizeof(void *) * size);
       const void **vals = (const void **)malloc (sizeof(void *) * size);
       CFDictionaryGetKeysAndValues((CFDictionaryRef)props, keys, vals);
       for(int k = 0; k < size; ++k) {
         printf("KEY: %s' - VAL: %s\n", CFStringGetCStringPtr((CFStringRef)keys[i], 0), "hi");
       }
       free(keys);
       free(vals);
     }
   }
   MIDIClientDispose(mc);
   */
#endif
  
  vstLoader *plug = new vstLoader();
  
  if(!plug->setPath(path)) {
    return 1;
  }
  else {
    plug->setName();
  }
  
  if(!plug->loadPlugin()) {
    delete plug;
    return 1;
  }
  
  if(!plug->initialize()) {
    delete plug;
    return 1;
  }
  
  // Set up time info for the plug
  _TIME.samplePos = 0;
  _TIME.sampleRate = DEF_SAMPLE_RATE;
  _TIME.nanoSeconds = 0;
  _TIME.ppqPos = 0;
  _TIME.tempo = DEF_TEMPO;
  _TIME.barStartPos = 0;
  _TIME.cycleStartPos = 0;
  _TIME.cycleEndPos = 0;
  _TIME.timeSigNumerator = DEF_TIMESIG_NUMER;
  _TIME.timeSigDenominator = DEF_TIMESIG_DENOM;
  _TIME.smpteOffset = 0;
  _TIME.smpteFrameRate = 0;
  _TIME.samplesToNextClock = 0;
  _TIME.flags = 0;
  
  // Set other plugin environment variables
  if(!plug->setSampleRate(DEF_SAMPLE_RATE)) {
    return 1;
  }
  
  if(!plug->setBlocksize(DEF_BLOCKSIZE)) {
    return 1;
  }
  
  // Initialize midi stuff
  MIDIClientRef mc;
  if(MIDIClientCreate(CFSTR(DEF_PRODUCT), NULL, NULL, &mc) != noErr) {
    debug(LOG_ERROR, "Could not initialize MIDI subsystem");
  }
  
  MIDIPortRef port;
  err = MIDIInputPortCreate(mc, CFSTR(DEF_PRODUCT), processMidi, plug, &port);
  MIDIEndpointRef endpoint = MIDIGetSource(0);
  err = MIDIPortConnectSource(port, endpoint, NULL);
  
  int result = 0;
  pthread_t run_thread;
  result = pthread_create(&run_thread, NULL, runPluginLoop, (void*)plug);
  openEditor(plug->getPluginPtr());
  
  pthread_kill(run_thread, SIGINT);
  MIDIPortDisconnectSource(port, endpoint);
  MIDIClientDispose(mc);
  delete plug;
  return 0;
}

float *_INPUTS[2] = { NULL, NULL };
float *_OUTPUTS[2] = { NULL, NULL };

OSStatus processData(void *inRefCon, AudioUnitRenderActionFlags *ioActionFlags, 
                     const AudioTimeStamp *inTimeStamp, UInt32 inBusNumber, 
                     UInt32 inNumberFrames, AudioBufferList *ioData) {
  static int bsize = inNumberFrames;
  if(bsize != inNumberFrames) {
    delete [] _INPUTS[0];
    delete [] _INPUTS[1];
    delete [] _OUTPUTS[0];
    delete [] _OUTPUTS[1];
    
    _INPUTS[0] = NULL;
    _INPUTS[1] = NULL;
    _OUTPUTS[0] = NULL;
    _OUTPUTS[1] = NULL;
    
    bsize = inNumberFrames;
    ((pluginLoader*)inRefCon)->setBlocksize(inNumberFrames);
  }
  
  if(_INPUTS[0] == NULL || _OUTPUTS[0] == NULL) {
    _INPUTS[0] = new float[inNumberFrames];
    _INPUTS[1] = new float[inNumberFrames];
    _OUTPUTS[0] = new float[inNumberFrames];
    _OUTPUTS[1] = new float[inNumberFrames];
  }
  
  ((pluginLoader*)inRefCon)->process(_INPUTS, _OUTPUTS, inNumberFrames);
  
	for(int frame = 0; frame < inNumberFrames; ++frame) {
    static_cast<SInt16*>(ioData->mBuffers[0].mData)[frame] = static_cast<SInt16>(_OUTPUTS[0][frame] * 32768. + 0.5);
    static_cast<SInt16*>(ioData->mBuffers[1].mData)[frame] = static_cast<SInt16>(_OUTPUTS[1][frame] * 32768. + 0.5);
	}
  
  _TIME.samplePos += inNumberFrames;
  _TIME.ppqPos = (_TIME.samplePos /  (60.0f / _TIME.tempo)) / _TIME.sampleRate;
  _TIME.barStartPos = (int)_TIME.ppqPos % (int)_TIME.timeSigNumerator;
  
  return noErr;
}

#if USE_PC_MIDI
void processMidi(const MIDIPacketList *pktlist, void *readProcRefCon, void *srcConnRefCon) {
  MIDIPacket *packet = const_cast<MIDIPacket*>(&pktlist->packet[0]);
  for(int i = 0; i < pktlist->numPackets; ++i) {
    ((pluginLoader*)readProcRefCon)->processMidi(packet->data[0], packet->data[1],
                                                 packet->data[2], packet->data[3]);
    packet = const_cast<MIDIPacket*>(MIDIPacketNext(packet));
  }
}
#endif

void *runPluginLoop(void *plug) {
  AudioUnit outputUnit;
  OSStatus err = noErr;
  
	// Open the default output unit
	ComponentDescription desc;
	desc.componentType = kAudioUnitType_Output;
	desc.componentSubType = kAudioUnitSubType_DefaultOutput;
	desc.componentManufacturer = kAudioUnitManufacturer_Apple;
	desc.componentFlags = 0;
	desc.componentFlagsMask = 0;
	
	Component comp = FindNextComponent(NULL, &desc);
	if(comp == NULL) { 
    debug(LOG_ERROR, "FindNextComponent failed");
    return NULL;
  }
	
	err = OpenAComponent(comp, &outputUnit);
	if(comp == NULL) {
    debug(LOG_ERROR, "OpenAComponent failed with error code %ld\n", err);
    return NULL;
  }
  
	// Set up a callback function to generate output to the output unit
  AURenderCallbackStruct input;
	input.inputProc = processData;
	input.inputProcRefCon = plug;
  
	err = AudioUnitSetProperty(outputUnit, kAudioUnitProperty_SetRenderCallback, kAudioUnitScope_Input,
                             0, &input, sizeof(input));
  
  AudioStreamBasicDescription streamFormat;
  streamFormat.mSampleRate = DEF_SAMPLE_RATE;
  streamFormat.mFormatID = kAudioFormatLinearPCM;
  streamFormat.mFormatFlags = kLinearPCMFormatFlagIsSignedInteger 
    | kLinearPCMFormatFlagIsBigEndian
    | kLinearPCMFormatFlagIsPacked
    | kAudioFormatFlagIsNonInterleaved;
  streamFormat.mBytesPerPacket = 2;
  streamFormat.mFramesPerPacket = 1;
  streamFormat.mBytesPerFrame = 2;
  streamFormat.mChannelsPerFrame = 2;	
  streamFormat.mBitsPerChannel = 16;	
  
  err = AudioUnitSetProperty(outputUnit, kAudioUnitProperty_StreamFormat,
                             kAudioUnitScope_Input, 0, &streamFormat,
                             sizeof(AudioStreamBasicDescription));
  if(err) {
    debug(LOG_ERROR, "AudioUnitSetProperty-SF failed with code %4.4s, %ld\n", (char*)&err, err);
    return NULL;
  }
  
  // Initialize unit
  err = AudioUnitInitialize(outputUnit);
  if(err) {
    debug(LOG_ERROR, "AudioUnitInitialize failed with code %ld\n", err);
    return NULL;
  }
  
  Float64 outSampleRate;
  UInt32 size = sizeof(Float64);
  err = AudioUnitGetProperty(outputUnit, kAudioUnitProperty_SampleRate,
                             kAudioUnitScope_Output, 0, &outSampleRate, &size);
  if(err) {
    debug(LOG_ERROR, "AudioUnitSetProperty-GF failed with code %4.4s, %ld\n", (char*)&err, err);
    return NULL;
  }
  
  // Start the rendering
  // The DefaultOutputUnit will do any format conversions to the format of the default device
  err = AudioOutputUnitStart(outputUnit);
  if(err) {
    debug(LOG_ERROR, "AudioOutputUnitStart failed with code %ld\n", err);
    return NULL;
  }
  
  // Loop until this thread is killed
  CFRunLoopRun();
  
  // REALLY after you're finished playing STOP THE AUDIO OUTPUT UNIT!!!!!!	
  // but we never get here because we're running until the process is nuked...	
  AudioOutputUnitStop(outputUnit);
  
  err = AudioUnitUninitialize(outputUnit);
  if(err) {
    debug(LOG_ERROR, "AudioUnitUninitialize failed with code %ld\n", err);
    return NULL;
  }
  
  return NULL;
}

void quit(int signal) {
  exit(signal);
}

#endif
#endif