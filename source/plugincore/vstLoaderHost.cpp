/*
 *  pluginLoaderHost.cpp - pluginCore
 *
 *  Created by Nik Reiman on 07.07.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 *  This source code may NOT be redistributed without express permission of Teragon Audio.  It may be used
 *  in free or commercial software works, but unauthorized duplication or resale in whole or part is
 *  strictly prohibited.
 */

#ifdef USE_PC_VST
#ifdef USE_PC_HOST

#ifndef __vstLoader_H
#include "vstLoader.h"
#endif

#ifdef MLOG_ENABLED
#ifndef __miniLogger_H
#include "miniLogger.h"
#endif
#endif

extern "C" {
  VstIntPtr VSTCALLBACK host(AEffect *effect, VstInt32 opcode, VstInt32 index,
                             VstInt32 value, void *ptr, float arg) {
    long retval = 0;
    
    switch(opcode) {
      // VST 1.0 opcodes
      case audioMasterVersion:
        // Input values: none
        // Return Value:
        // 0 or 1 for old version
        // 2 or higher for VST2.0 host?
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for master version");
#endif
        retval = 2;
        break;
      case audioMasterAutomate:
        // Input values:
        // <index> parameter that has changed
        // <opt> new value
        // Return value: 0
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked to automate parameter %d (new value: %f)", index, value);
#endif
        retval = 0;
        break;
      case audioMasterCurrentId:
        // Input values: none
        // Return Value
        // the unique id of a plug that's currently loading
        // zero is a default value and can be safely returned if not known
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for current ID");
#endif
        retval = 0;
        break;
      case audioMasterIdle:
        // Input values: none
        // Return Value: 0
        // Note: idle routine should also call effEditIdle for all open editors
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for idle");
#endif
        effect->dispatcher(effect, effEditIdle, 0, 0, 0, 0);
        break;
      case audioMasterPinConnected:
        // Input values:
        // <index> pin to be checked
        // <value> 0=input pin, non-zero value=output pin
        // Return values:
        // 0=true, non-zero=false
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for pin connected status");
#endif
        break;
        
        // VST 2.0 opcodes
      case audioMasterGetTime:
        // Input Values:
        // <value> should contain a mask indicating which fields are required
        // Return Value:
        // ptr to populated const VstTimeInfo structure (or 0 if not supported)
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for current time");
#endif
        break;
      case audioMasterProcessEvents:
        // Input Values:
        // <ptr> Pointer to a populated VstEvents structure
        // Return value:
        // 0 if error
        // 1 if OK
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for events to process");
#endif
        break;
      case audioMasterIOChanged:
        // Input Values: None
        // Return Value:
        // 0 if error
        // non-zero value if OK
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked if I/O has changed");
#endif
        break;
      case audioMasterSizeWindow:
        // Input Values:
        // <index> width
        // <value> height
        // Return Value:
        // 0 if error
        // non-zero value if OK
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for window size");
#endif
        break;
      case audioMasterGetSampleRate:
        // Input Values: None
        // Return Value: 0
        
        // Note: Host must despatch effSetSampleRate to the plug in response to this call
        // \todo Check despatcher notes for any return codes from effSetSampleRate
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for sample rate");
        effect->dispatcher(effect, effSetSampleRate, 0, 0, NULL, _OPT.getFloat(OPT_SAMPLE_RATE));
#else
        effect->dispatcher(effect, effSetSampleRate, 0, 0, NULL, DEF_SAMPLE_RATE);
#endif
        break;
      case audioMasterGetBlockSize:
        // Input Values: None
        // Return Value: 0
        
        // Note: Host must despatch effSetBlockSize to the plug in response to this call
        // \todo Check despatcher notes for any return codes from effSetBlockSize
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for block size");
        effect->dispatcher(effect, effSetBlockSize, 0, _OPT.getInt(OPT_BLOCKSIZE), NULL, 0.0f);
#else
        effect->dispatcher(effect, effSetBlockSize, 0, DEF_BLOCKSIZE, NULL, 0.0f);
#endif
        break;
      case audioMasterGetInputLatency:
        // Input Values: None
        // Return Value:
        // input latency (in sampleframes?)
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for input latency");
#endif
        break;
      case audioMasterGetOutputLatency:
        // Input Values: None
        // Return Value:
        // output latency (in sampleframes?)
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for output latency");
#endif
        break;
      case audioMasterGetCurrentProcessLevel:
        // Input Values: None
        // Return Value:
        // 0: not supported,
        // 1: currently in user thread (gui)
        // 2: currently in audio thread (where process is called)
        // 3: currently in 'sequencer' thread (midi, timer etc)
        // 4: currently offline processing and thus in user thread
        // other: not defined, but probably pre-empting user thread.
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for current process level");
#endif
        break;
      case audioMasterGetAutomationState:
        // Input Values: None
        // Return Value:
        // 0: not supported
        // 1: off
        // 2: read
        // 3: write
        // 4: read/write
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for automation state");
#endif
        break;
      case audioMasterGetVendorString:
        // Input Values:
        // <ptr> string (max 64 chars) to be populated
        // Return Value:
        // 0 if error
        // non-zero value if OK
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for vendor string");
#endif
        strncpy((char*)ptr, (char*)ORG_NAME_FULL, 64);
        retval = 1;
        break;
      case audioMasterGetProductString:
        // Input Values:
        // <ptr> string (max 64 chars) to be populated
        // Return Value:
        // 0 if error
        // non-zero value if OK
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for product string");
#endif
#ifdef DEF_PRODUCT
        strncpy((char*)ptr, (char*)DEF_PRODUCT, 64);
        retval = 1;
#else
        retval = 0;
#endif
        break;
      case audioMasterGetVendorVersion:
        // Input Values: None
        // Return Value:
        // Vendor specific host version as integer
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for vendor version");
#endif
        retval = 1000;
        break;
      case audioMasterVendorSpecific:
        // Input Values:
        // <index> lArg1
        // <value> lArg2
        // <ptr> ptrArg
        // <opt>	floatArg
        // Return Values:
        // Vendor specific response as integer
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for vendor specific version");
#endif
        break;
      case audioMasterCanDo:
        // Input Values:
        // <ptr> predefined "canDo" string
        // Return Value:
        // 0 = Not Supported
        // non-zero value if host supports that feature
        
        //Note: Possible Can Do strings are:
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked if we canDo %f", arg);
#endif
        retval = 0;
        break;
      case audioMasterGetLanguage:
        // Input Values: None
        // Return Value:
        // kVstLangEnglish
        // kVstLangGerman
        // kVstLangFrench
        // kVstLangItalian
        // kVstLangSpanish
        // kVstLangJapanese
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for host language");
#endif
        retval = kVstLangEnglish;
        break;
      case audioMasterGetDirectory:
        // Input Values: None
        // Return Value:
        // 0 if error
        // FSSpec on MAC, else char* as integer
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for the current directory");
#endif
#if MAC
        FSRef ret_ref;
        FSSpec ret_spec;
        
        char *cwd = new char[MAX_PATH_SIZE];
        getcwd(cwd, sizeof(char) * MAX_PATH_SIZE);
        OSStatus err = FSPathMakeRef((const UInt8*)cwd, &ret_ref, false);
        err = FSGetCatalogInfo(&ret_ref, kFSCatInfoNone, NULL, NULL, &ret_spec, NULL);
        delete [] cwd;
        
        retval = 1;
#else
        // \todo Current dir for windows
#endif
        break;
      case audioMasterUpdateDisplay:
        // Input Values: None
        // Return Value: Unknown
        // \todo ^^ Look this up
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked us to update the display");
#endif
        break;
      case audioMasterOfflineStart:
        ///< [index]: numNewAudioFiles [value]: numAudioFiles [ptr]: #VstAudioFile*  @see AudioEffectX::offlineStart
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for offline start");
#endif
        break;
      case audioMasterOfflineRead:
				//< [index]: bool readSource [value]: #VstOfflineOption* @see VstOfflineOption [ptr]: #VstOfflineTask*  @see VstOfflineTask @see AudioEffectX::offlineRead
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for offline read");
#endif
        break;
      case audioMasterOfflineWrite:
        ///< @see audioMasterOfflineRead @see AudioEffectX::offlineRead
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for offline write");
#endif
        break;
      case audioMasterOfflineGetCurrentPass:
        ///< @see AudioEffectX::offlineGetCurrentPass
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for current offline pass");
#endif
        break;
      case audioMasterOfflineGetCurrentMetaPass:
        ///< @see AudioEffectX::offlineGetCurrentMetaPass
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for current offline meta pass");
#endif
        break;
      case audioMasterBeginEdit:
        ///< [index]: parameter index  @see AudioEffectX::beginEdit
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for begin parameter edit");
#endif
        break;
      case audioMasterEndEdit:
        ///< [index]: parameter index  @see AudioEffectX::endEdit
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for end parameter edit");
#endif
        break;
      case audioMasterOpenFileSelector:
        ///< [ptr]: VstFileSelect* [return value]: 1 if supported  @see AudioEffectX::openFileSelector
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for a file selector to be opened");
#endif
        break;
      case audioMasterCloseFileSelector:
        ///< [ptr]: VstFileSelect*  @see AudioEffectX::closeFileSelector
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for the the file selector to be closed");
#endif
        break;
        
        // Deprecated pre-2.4 calls
      case audioMasterOpenWindow:
        // Input Values:
        // <ptr> pointer to a VstWindow structure
        // Return Value:
        // 0 if error
        // else platform specific ptr
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for a VstWindow to be opened");
#endif
        break;
      case audioMasterCloseWindow:
        // Input Values:
        // <ptr> pointer to a VstWindow structure
        // Return Value:
        // 0 if error
        // Non-zero value if OK
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for the VstWindow to be closed");
#endif
        break;
      case audioMasterSetTime:
        // Ignored
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked to set the master time");
#endif
        break;
      case audioMasterTempoAt:
        // Input Values:
        // <value> sample frame location to be checked
        // Return Value:
        // tempo (in bpm * 10000)
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for tempo at %d", value);
#endif
        break;
      case audioMasterGetNumAutomatableParameters:
        // Input Values:
        // None
        // Return Value:
        // number of automatable parameters
        // zero is a default value and can be safely returned if not known
        
        //NB - what exactly does this mean? can the host set a limit to the
        //number of parameters that can be automated?
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for number of automatable parameters");
#endif
        break;
      case audioMasterGetParameterQuantization:
        // Input Values: None
        // Return Value:
        // integer value for +1.0 representation,
        // or 1 if full single float precision is maintained
        // in automation.
        
        //NB - ***possibly bugged***
        //Steinberg notes say "parameter index in <value> (-1: all, any)"
        //but in aeffectx.cpp no parameters are taken or passed
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked for parameter quantization");
#endif
        break;
      case audioMasterGetPreviousPlug:
        // Input Values: None
        // Return Value:
        // pointer to AEffect structure or NULL if not known?
        
        //NB - ***possibly bugged***
        //Steinberg notes say "input pin in <value> (-1: first to come)"
        //but in aeffectx.cpp no parameters are taken or passed
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked us for the previous plugin");
#endif
        break;
      case audioMasterGetNextPlug:
        // Input Values: None
        // Return Value:
        // pointer to AEffect structure or NULL if not known?
        
        //NB - ***possibly bugged***
        //Steinberg notes say "output pin in <value> (-1: first to come)"
        //but in aeffectx.cpp no parameters are taken or passed
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked us for the next plugin");
#endif
        break;
      case audioMasterWillReplaceOrAccumulate:
        // Input Values: None
        // Return Value:
        // 0: not supported
        // 1: replace
        // 2: accumulate
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked if host will replace or accumulate");
#endif
        retval = 1;
        break;
      case audioMasterWantMidi:
        // Input Values:
        // <value> filter flags (which is currently ignored, no defined flags?)
        // Return Value: 0
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug wants midi");
#endif
        break;
      case audioMasterNeedIdle:
        // Input Values: None
        // Return Value:
        // 0 if error
        // non-zero value if OK
        
        //NB plug needs idle calls (outside its editor window)
        //this means that effIdle must be dispatched to the plug
        //during host idle process and not effEditIdle calls only when its
        //editor is open
        //Check despatcher notes for any return codes from effIdle
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug needs idle");
#endif
        break;
      case audioMasterSetIcon:
#ifdef MLOG_ENABLED
        mlog(LOG_INFO, "Plug asked to set icon");
#endif
        break;        
      default:
#ifdef MLOG_ENABLED
        mlog(LOG_WARN, "Unknown opcode %d requested from host", opcode);
#endif
        break;
    }
    
    return retval;
  }
}

#endif
#endif