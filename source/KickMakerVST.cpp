/*
 *  KickMaker - KickMakerVST.cpp
 *  Created by Nik Reiman on 03.02.06
 *  Copyright (c) 2006 Teragon Audio, All rights reserved
 */

#ifndef __KickMakerVST_H
#include "KickMakerVST.h"
#endif

#ifndef __KickMakerEditor_H
#include "KickMakerEditor.h"
#endif

#ifndef __defaults_H
#include "defaults.h"
#endif

#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////

AudioEffect* createEffectInstance(audioMasterCallback audioMaster) {
	return new KickMaker(audioMaster);
}

KickMaker::KickMaker(audioMasterCallback audioMaster)
: AudioEffectX(audioMaster, 0, NUM_PARAMS) {
  if(audioMaster) {
    setNumInputs(NUM_INPUTS);
    setNumOutputs(NUM_OUTPUTS);
    setUniqueID(UNIQUE_ID);
    canProcessReplacing();
    isSynth();
  }
  
  initProcess();
  suspend();
  programsAreChunks(true);
  
  editor = new KickMakerEditor(this);
  core = new KickMakerCore(NUM_PARAMS, VERSION, DEF_PRODUCT);
  core->setParameter(PRM_SAMPLE_RATE, getSampleRate(), true);
  ((KickMakerEditor*)editor)->setCore(core);
}

KickMaker::~KickMaker() {
  delete core;
}

VstInt32 KickMaker::canDo(char *text) {
  if(!strcmp(text, "receiveVstEvents")) {
		return 1;
  }
  if(!strcmp(text, "receiveVstMidiEvent")) {
		return 1;
  }
	if(!strcmp(text, "midiProgramNames")) {
		return 1;
  }
	return -1; // -1 => explicitly can't do; 0 => don't know
}

bool KickMaker::canParameterBeAutomated(VstInt32 index) {
  return true;
}

bool KickMaker::copyProgram(long destination) {
  return false;
}

void KickMaker::fillProgram(VstInt32 channel, VstInt32 prg, MidiProgramName *mpn) {
	mpn->midiBankMsb = -1;
	mpn->midiBankLsb = -1;
	mpn->reserved = 0;
	mpn->flags = 0;
  strncpy(mpn->name, "Standard", 63);
  mpn->midiProgram = 0;
  mpn->parentCategoryIndex = 0;
}

void KickMaker::initProcess() {
}

VstInt32 KickMaker::getChunk(void **data, bool isPreset) {
  int datasize = 0;
  *data = core->getState(datasize);
  return datasize;
}

VstInt32 KickMaker::getCurrentMidiProgram(VstInt32 channel, MidiProgramName *mpn) {
	if(channel < 0 || channel >= 16 || !mpn) {
		return -1;
  }
  
  // TODO: Look up your current MIDI program
	VstInt32 prg = 0;
	mpn->thisProgramIndex = prg;
	fillProgram(channel, prg, mpn);
	return prg;
}

bool KickMaker::getEffectName(char* name) {
  strncpy(name, "KickMaker", kVstMaxEffectNameLen);
  return true;
}

bool KickMaker::getMidiKeyName(VstInt32 channel, MidiKeyName *key) {
	// TODO: Fill in this information
  // key->thisProgramIndex;		// >= 0. fill struct for this program index.
	// key->thisKeyNumber;			// 0 - 127. fill struct for this key number.
	key->keyName[0] = 0;
	key->reserved = 0;				// zero
	key->flags = 0;					// reserved, none defined yet, zero.
	return true;
}

VstInt32 KickMaker::getMidiProgramCategory(VstInt32 channel, MidiProgramCategory *category) {
	category->parentCategoryIndex = -1; // no parent category
	category->flags = 0; // reserved, none defined yet
  category->name[0] = 0;
	return 0;
}

VstInt32 KickMaker::getMidiProgramName(VstInt32 channel, MidiProgramName *mpn) {
	VstInt32 prg = mpn->thisProgramIndex;
	if(prg < 0 || prg >= 128) {
		return 0;
  }
	fillProgram(channel, prg, mpn);
	if(channel == 9) {
		return 1;
  }
  return 128;
}

VstInt32 KickMaker::getNumMidiInputChannels() {
  return 1;
}

VstInt32 KickMaker::getNumMidiOutputChannels() {
  return 0;
}

bool KickMaker::getOutputProperties(VstInt32 index, VstPinProperties *properties) {
  if(index < NUM_OUTPUTS) {
    sprintf(properties->label, "%1d Out", index + 1);
		properties->flags = kVstPinIsActive;
		if(index < 2) {
			properties->flags |= kVstPinIsStereo;
    }
    return true;
  }
  return false;
}

float KickMaker::getParameter(VstInt32 index) {
  return core->getParameter(REQ_VALUE, index, 0);
}

void KickMaker::getParameterDisplay(VstInt32 index, char *text) {
  core->getParameter(REQ_DISPLAY, index, text);
}

void KickMaker::getParameterLabel(VstInt32 index, char *text) {
  core->getParameter(REQ_LABEL, index, text);
}

void KickMaker::getParameterName(VstInt32 index, char *text) {
  core->getParameter(REQ_NAME, index, text);
}

VstPlugCategory KickMaker::getPlugCategory() { 
  return kPlugCategSynth;
}

bool KickMaker::getProductString(char* text) {
  strncpy(text, "KickMaker", kVstMaxProductStrLen);
  return true;
}

VstInt32 KickMaker::getProgram() {
  return core->getCurrentPresetIndex();
}

void KickMaker::getProgramName(char *name) {
  core->getCurrentPresetName(name);
}

bool KickMaker::getProgramNameIndexed(VstInt32 category, VstInt32 index, char *text) {
  core->getPresetName(index, text);
  return true;
}

bool KickMaker::getVendorString(char* text) {
  strncpy(text, "Teragon Audio", kVstMaxVendorStrLen);
  return true;
}

VstInt32 KickMaker::getVendorVersion() {
  return 1000;
}

bool KickMaker::hasMidiProgramsChanged(VstInt32 channel) {
  return false;
}

VstInt32 KickMaker::processEvents(VstEvents* ev) {
  for(VstInt32 i = 0; i < ev->numEvents; i++) {
		if((ev->events[i])->type != kVstMidiType) {
			continue;
    }
    
		VstMidiEvent* event = (VstMidiEvent*)ev->events[i];
    core->processMidi(event->midiData[0] & 0xf0, (event->midiData[0] << 4) & 0xf0,
                      event->midiData[1], event->midiData[2], event->deltaFrames);
  }
	return 1;
}

void KickMaker::process(float **inputs, float **outputs, VstInt32 sampleFrames) {
  core->process(inputs, outputs, sampleFrames);
}

void KickMaker::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames) {
  core->process(inputs, outputs, sampleFrames);
}

void KickMaker::setBlockSize(VstInt32 blockSize) {
	AudioEffectX::setBlockSize(blockSize);
}

void KickMaker::setParameter(VstInt32 index, float value) {
  core->setParameterNormalized(index, value);
  if(editor) {
    ((KickMakerEditor*)editor)->updateControl(index);
  }
}

VstInt32 KickMaker::setChunk(void *data, VstInt32 byteSize, bool isPreset) {
  return core->setState(reinterpret_cast<unsigned char*>(data), byteSize);
}

void KickMaker::setParameterAutomated(VstInt32 index, float value) {
  AudioEffectX::setParameterAutomated(index, value);
}

void KickMaker::setProgram(VstInt32 index) {
  core->loadPreset(index);
  curProgram = index;
}

void KickMaker::setProgramName(char *name) {
}

void KickMaker::setSampleRate(float sampleRate) {
	AudioEffectX::setSampleRate(sampleRate);
}