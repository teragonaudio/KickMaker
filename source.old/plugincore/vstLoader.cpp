/*
 *  vstLoader.cpp
 *  MissWatson
 *
 *  Created by Nik Reiman on 23.07.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#if USE_PC_VST
#if USE_PC_HOST

#ifndef __vstLoader_H
#include "vstLoader.h"
#endif

vstLoader::vstLoader() : pluginLoader()
{
  m_dispatch = 0;
  m_host_ptr = 0;
  m_plugin = 0;
}

vstLoader::~vstLoader()
{
}

void* vstLoader::getPluginPtr() const
{
  return (void*)m_plugin;
}

int vstLoader::getNumParameters() const {
  return m_plugin->numParams;
}

float vstLoader::getParameter(int index) const {
  return m_plugin->getParameter(m_plugin, index);
}

bool vstLoader::loadPlugin()
{
#if MAC
  // Try the newer bundle format first, then fall back on the old-school CFM format
  debug(LOG_INFO, "Attempting load of MachO plugin");
  if(!loadBundlePlugin())
  {
    debug(LOG_INFO, "Attempting load of CFM plugin");
    if(!loadCFMPlugin())
    {
      return false;
    }
    else
    {
      debug(LOG_INFO, "Plugin '%s' successfully loaded from CFM file", m_name);
      return true;
    }
  }
  else
  {
    debug(LOG_INFO, "Plugin '%s' successfully loaded from bundle resources", m_name);
    return true;
  }
#endif
#if WINDOWS
  debug(LOG_INFO, "Attempting load of DLL plugin");
  if(!loadDLLPlugin())
  {
    return false;
  }
  else
  {
    debug(LOG_INFO, "Plugin '%s' successfully loaded from DLL", m_name);
    return true;
  }
  
  return false;
#endif
}

#if MAC
bool vstLoader::loadBundlePlugin()
{
  m_host_ptr = host;
  
  CFStringRef path_str = CFStringCreateWithCString(NULL, (const char*)&m_path, kCFStringEncodingASCII);
  CFURLRef bundle_url = CFURLCreateWithFileSystemPath(kCFAllocatorDefault, path_str, kCFURLPOSIXPathStyle, true);
  if(bundle_url == NULL)
  {
    debug(LOG_WARN, "Couldn't make URL reference for plugin");
    CFRelease(path_str);
    return false;
  }
  
  CFBundleRef bundle = CFBundleCreate(kCFAllocatorDefault, bundle_url);
  if(bundle == NULL)
  {
    debug(LOG_WARN, "Couldn't create bundle reference");
    CFRelease(path_str);
    CFRelease(bundle_url);
    return false;
  }
  
  debug(LOG_INFO, "Loading plugin from resources");
  if(!CFBundleLoadExecutable(bundle))
  {
    debug(LOG_ERROR, "Plugin is not executable");
    CFRelease(path_str);
    CFRelease(bundle_url);
    CFRelease(bundle);
    return false;
  }
  
  debug(LOG_INFO, "Finding plugin's main()");
  vstPluginFuncPtr main_address = NULL;
  main_address = (vstPluginFuncPtr)CFBundleGetFunctionPointerForName(bundle, CFSTR("VSTPluginMain"));
  // Maybe it's a pre-2.4 plugin instead
  if(main_address == NULL)
  {
    main_address = (vstPluginFuncPtr)CFBundleGetFunctionPointerForName(bundle, CFSTR("main_macho"));
  }
  
  if(main_address != NULL)
  {
    m_plugin = main_address(m_host_ptr);
    if(m_plugin == NULL)
    {
      debug(LOG_ERROR, "Plugin's main() returns null");
      CFBundleUnloadExecutable(bundle);
      CFRelease(path_str);
      CFRelease(bundle_url);
      CFRelease(bundle);
      return false;
    }
    else if(m_plugin->magic != kEffectMagic)
    {
      debug(LOG_ERROR, "Plugin's magic number is bad");
      CFBundleUnloadExecutable(bundle);
      CFRelease(path_str);
      CFRelease(bundle_url);
      CFRelease(bundle);
      return false;
    }
    debug(LOG_INFO, "Creating dispatcher handler");
    m_dispatch = m_plugin->dispatcher;
  }
  else
  {
    debug(LOG_ERROR, "Couldn't get a pointer to plugin's main()");
    CFBundleUnloadExecutable(bundle);
    CFRelease(path_str);
    CFRelease(bundle_url);
    CFRelease(bundle);
    return false;
  }
  
  // When these are uncommented, bad things happen!  Don't ask me why!
  // CFRelease(bundle);
  // CFBundleUnloadExecutable(bundle);
  
  CFRelease(path_str);
  CFRelease(bundle_url);
  return true;
}
#endif

#if MAC
bool vstLoader::loadCFMPlugin()
{
  CFragConnectionID connection_id;
  Str255 error_msg;
  OSStatus err;
  FSSpec fs_tmp = getFSSpec();
  vstPluginFuncPtr main_address = NULL;
  
  m_host_ptr = (audioMasterCallback)makeMachOPtr((void*)host);
  
  short plug_ref = FSpOpenResFile(&fs_tmp, fsRdPerm);
  err = ResError();
  if(err == noErr)
  {
    Handle plug_handle = Get1IndResource('aEff', 1);
    
    if(plug_handle != NULL)
    {
      debug(LOG_INFO, "Locking resource");
      DetachResource(plug_handle);
      HLock(plug_handle);
      debug(LOG_INFO, "Getting memory fragment");
      err = GetMemFragment(*plug_handle, GetHandleSize(plug_handle), fs_tmp.name,
                           kPrivateCFragCopy, &connection_id, (Ptr*)&main_address, error_msg);
      if(err != noErr)
      {
        debug(LOG_ERROR, "Could not locate main address in memory fragment");
        HUnlock(plug_handle);
        CloseResFile(plug_ref);
        return false;
      }
    }
    else
    {
      debug(LOG_ERROR, "Could not retrieve plugin handle");
      return false;
    }
  }
  else
  {
    debug(LOG_WARN, "Could not open plugin resources");
    return false;
  }
  
  if(main_address != NULL)
  {
    debug(LOG_INFO, "Getting pointer to plugin's main()");
    vstPluginFuncPtr plugin_ptr = (vstPluginFuncPtr)makeCFMPtr((void*)main_address);
    m_plugin = plugin_ptr(m_host_ptr);
    if(m_plugin->magic != kEffectMagic)
    {
      debug(LOG_ERROR, "Plugin's magic number is bad");
      CloseResFile(plug_ref);
      return false;
    }
    debug(LOG_INFO, "Creating dispatcher handler");
    m_dispatch = (dispatcherFuncPtr)makeCFMPtr((void*)m_plugin->dispatcher);
    
    debug(LOG_INFO, "Setting up plugin callback functions");
    m_plugin->getParameter = (getParameterFuncPtr)makeCFMPtr((void*)m_plugin->getParameter);
    m_plugin->processReplacing = (processFuncPtr)makeCFMPtr((void*)m_plugin->processReplacing);
    m_plugin->setParameter = (setParameterFuncPtr)makeCFMPtr((void*)m_plugin->setParameter);
  }
  else
  {
    debug(LOG_ERROR, "Couldn't get a pointer to plugin's main()");
    return false;
  }
  
  CloseResFile(plug_ref);
  return true;
}
#endif

#if WINDOWS
bool vstLoader::loadDLLPlugin()
{
  HMODULE module = LoadLibrary(m_path);
  vstPluginFuncPtr main_entry = (vstPluginFuncPtr)GetProcAddress(module, "VSTPluginMain");
  if(!m_plugin)
  {	
    main_entry = (vstPluginFuncPtr)GetProcAddress((HMODULE)module, "main");
  }
  m_plugin = main_entry(host);
  if(m_plugin->magic != kEffectMagic)
  {  
    debug(LOG_ERROR, "Plugin's magic number is bad");  
    return false;
  }
  
  debug(LOG_INFO, "Creating dispatcher handler");
  m_dispatch = (dispatcherFuncPtr)m_plugin->dispatcher;
  
  debug(LOG_INFO, "Setting up plugin callback functions");
  m_plugin->getParameter = (getParameterFuncPtr)m_plugin->getParameter;
  m_plugin->processReplacing = (processFuncPtr)m_plugin->processReplacing;
  m_plugin->setParameter = (setParameterFuncPtr)m_plugin->setParameter;
  
  return true;
}
#endif

#if MAC
void* vstLoader::makeMachOPtr(void *addr)
{
  void *newAddr = NewPtr(8);
  ((void**)newAddr)[0] = addr;
  ((void**)newAddr)[1] = newAddr;
  return newAddr;
}
#endif

#if MAC
void* vstLoader::makeCFMPtr(void *cfmfp)
{
  UInt32 gluetab[6] = {0x3D800000, 0x618C0000, 0x800C0000, 0x804C0004, 0x7C0903A6, 0x4E800420};
  // Must later dispose of this allocated memory
  UInt32 *mfp = (UInt32*)NewPtr(sizeof(gluetab));
  
  mfp[0] = gluetab[0] | ((UInt32)cfmfp >> 16);
  mfp[1] = gluetab[1] | ((UInt32)cfmfp & 0xFFFF);
  mfp[2] = gluetab[2];
  mfp[3] = gluetab[3];
  mfp[4] = gluetab[4];
  mfp[5] = gluetab[5];
  MakeDataExecutable(mfp, sizeof(gluetab));
  return(mfp);
}
#endif

// Open the plugin and prepare it to receive audio/midi data
bool vstLoader::initialize()
{
  debug(LOG_INFO, "Opening plugin via dispatcher");
  m_dispatch(m_plugin, effOpen, 0, 0, NULL, 0.0f);
  resume();
  return true;
}

void vstLoader::printInfo() const
{
  debug(LOG_INFO, "Plugin Information:");
  char uidStr[5];
  for(int i = 0; i < 4; ++i) {
    uidStr[i] = (char)((m_plugin->uniqueID >> ((3 - i) * 8)) & 0xff);
  }
  uidStr[4] = '\0';

  debug(LOG_INFO, "  Unique ID: '%s' (%d)", uidStr, m_plugin->uniqueID);
  debug(LOG_INFO, "  Inputs: %d", m_plugin->numInputs);
  debug(LOG_INFO, "  Initial Delay: %d", m_plugin->initialDelay);
  debug(LOG_INFO, "  Outputs: %d", m_plugin->numOutputs);
  debug(LOG_INFO, "  Parameters: %d", m_plugin->numParams);
  debug(LOG_INFO, "  Plugin Version: %d", m_plugin->version);
  debug(LOG_INFO, "  Programs: %d", m_plugin->numPrograms);
  
  // Obsolete as of VST 2.4
  debug(LOG_INFO, "  I/O Ratio: %f", m_plugin->ioRatio);
  debug(LOG_INFO, "  Off Qualities: %d", m_plugin->offQualities);
  debug(LOG_INFO, "  Real Qualities: %d", m_plugin->realQualities);
  
  if(m_dispatch(m_plugin, effGetVstVersion, 0, 0, NULL, 0.0f) == 2)
  {
    debug(LOG_INFO, "  VST Version: 2.x");
  }
  else
  {
    debug(LOG_INFO, "  VST Version: 1.0");
  }
  
  debug(LOG_INFO, "Plugin Capabilities:");
  
  // VST 1.0 flags
  if(m_plugin->flags & effFlagsProgramChunks)
  {
    debug(LOG_INFO, "  + Chunk support");
  }
  if(m_plugin->flags & effFlagsHasEditor)
  {
    debug(LOG_INFO, "  + GUI editor");
  }
  // Obsolete as of VST 2.4
  if(m_plugin->flags & effFlagsHasClip)
  {
    debug(LOG_INFO, "  + Clipping display");
  }
  // Obsolete as of VST 2.4
  if(m_plugin->flags & effFlagsCanMono)
  {
    debug(LOG_INFO, "  + Mono");
  }
  // Obsolete as of VST 2.4
  if(m_plugin->flags & effFlagsCanReplacing)
  {
    debug(LOG_INFO, "  + Process replacing");
  }
  // Obsolete as of VST 2.4
  if(m_plugin->flags & effFlagsHasVu)
  {
    debug(LOG_INFO, "  + VU display");
  }
    
  // VST 2.x flags
  if(m_dispatch(m_plugin, effGetVstVersion, 0, 0, NULL, 0.0f) == 2)
  {
    // Obsolete as of VST 2.4
    if(m_plugin->flags & effFlagsExtIsAsync)
    {
      debug(LOG_INFO, "  + External async");
    }
    // Obsolete as of VST 2.4
    if(m_plugin->flags & effFlagsExtHasBuffer)
    {
      debug(LOG_INFO, "   + External buffer");
    }
    
    if(m_plugin->flags & effFlagsNoSoundInStop)
    {
      debug(LOG_INFO, "  + No stop sound");
    }
    if(m_plugin->flags & effFlagsIsSynth)
    {
      debug(LOG_INFO, "  + Synth");
    }
    
    debug(LOG_INFO, "Plugin Can Do's:");
    
    if(m_dispatch(m_plugin, effCanDo, 0, 0, (void*)"plugAsChannelInsert", 0.0f) > 0)
    {
      debug(LOG_INFO, "  + Channel insert");
    }
    if(m_dispatch(m_plugin, effCanDo, 0, 0, (void*)"mixDryWet", 0.0f) > 0)
    {
      debug(LOG_INFO, "  + Mix dry/wet");
    }
    if(m_dispatch(m_plugin, effCanDo, 0, 0, (void*)"offline", 0.0f) > 0)
    {
      debug(LOG_INFO, "  + Offline processing");
    }
    if(m_dispatch(m_plugin, effCanDo, 0, 0, (void*)"sendVstEvents", 0.0f) > 0)
    {
      debug(LOG_INFO, "  + Send VST events");
    }
    if(m_dispatch(m_plugin, effCanDo, 0, 0, (void*)"sendVstMidiEvent", 0.0f) > 0)
    {
      debug(LOG_INFO, "  + Send VST MIDI events");
    }
    if(m_dispatch(m_plugin, effCanDo, 0, 0, (void*)"sendVstTimeInfo", 0.0f) > 0)
    {
      debug(LOG_INFO, "  + Send VST time info");
    }
    if(m_dispatch(m_plugin, effCanDo, 0, 0, (void*)"receiveVstEvents", 0.0f) > 0)
    {
      debug(LOG_INFO, "  + Receive VST events");
    }
    if(m_dispatch(m_plugin, effCanDo, 0, 0, (void*)"receiveVstMidiEvent", 0.0f) > 0)
    {
      debug(LOG_INFO, "  + Receive VST MIDI events");
    }
    if(m_dispatch(m_plugin, effCanDo, 0, 0, (void*)"receiveVstTimeInfo", 0.0f) > 0)
    {
      debug(LOG_INFO, "  + Receive VST time info");
    }
    if(m_dispatch(m_plugin, effCanDo, 0, 0, (void*)"plugAsSend", 0.0f) > 0)
    {
      debug(LOG_INFO, "  + Send");
    }
  }
  
  char text[32];
  if(m_plugin->numParams > 0) {
    debug(LOG_INFO, "Parameters:");
    for(int i = 0; i < m_plugin->numParams; ++i)
    {
      memset(text, 0x0, sizeof(char) * 32);
      m_dispatch(m_plugin, effGetParamName, i, 0, (char*)&text, 0);
      debug(LOG_INFO, "  %d: %s", i, text);
    }
  }
  
  if(m_plugin->numPrograms > 0) {
    debug(LOG_INFO, "Programs:");
    // This is unfortunately rather inconvenient... the VST spec only allows you
    // to get the name of the currently running program name instead of an arbitrary
    // one.  So we need to preserve the state of all parameters before doing this
    // query on the plugin.
    float *oldParams = new float[m_plugin->numParams];
    for(int i = 0; i < m_plugin->numParams; ++i) {
      oldParams[i] = getParameter(i);
    }
    
    for(int i = 0; i < m_plugin->numPrograms; ++i) {
      m_dispatch(m_plugin, effSetProgram, 0, i, NULL, 0.0f);
      memset(text, 0x0, sizeof(char) * 32);
      m_dispatch(m_plugin, effGetProgramName, i, 0, (char*)&text, 0);
      debug(LOG_INFO, "  %d: %s", i, text);
    }
    
    // Now restore plugin parameters to their previous settings
    for(int i = 0; i < m_plugin->numParams; ++i) {
      // We aren't using this->setParameter() because that discards the const qualifier
      m_plugin->setParameter(m_plugin, i, oldParams[i]);
    }
    delete [] oldParams;
  }
}

void vstLoader::process(float **inputs, float **outputs, long frames)
{
  m_plugin->processReplacing(m_plugin, inputs, outputs, frames);
}

void vstLoader::processMidi(int type, int byte1, int byte2, long frames)
{
  if(m_plugin->flags & effFlagsIsSynth || 
     m_dispatch(m_plugin, effCanDo, 0, 0, (void*)"receiveVstEvents", 0.0f) > 0)
  {
    VstMidiEvent m;
    VstEvents e;
    
    m.type = kVstMidiType;
    m.byteSize = 24; // Three bytes
    m.flags = 0;
    m.deltaFrames = frames;
    
    m.midiData[0] = (char)type;
    m.midiData[1] = (char)byte1;
    m.midiData[2] = (char)byte2;
    m.midiData[3] = 0x0;
    
    e.numEvents = 1;
    e.events[0] = (VstEvent*)&m;
    
    debug(LOG_VERBOSE, "Dispatching midi event of type %d @ %d, %d in %d frames",
         type, byte1, byte2, frames);
    m_dispatch(m_plugin, effProcessEvents, 0, 0, &e, 0.0f);
  }
}

void vstLoader::resume()
{
  debug(LOG_INFO, "Resuming plugin");
  m_dispatch(m_plugin, effMainsChanged, 0, 1, NULL, 0.0f);
}

bool vstLoader::setBlocksize(int bsize)
{
  suspend();
  debug(LOG_INFO, "Setting blocksize to %d", bsize);
  m_dispatch(m_plugin, effSetBlockSize, 0, bsize, NULL, 0.0f);
  resume();
  return true;
}

bool vstLoader::setParameter(int index, float value, long frames) {
  // TODO: Only fetch name for LOG_VERBOSE -- this is wasteful
//  char pname[MAX_PLUG_NAME];
//  memset(pname, 0x0, sizeof(char) * MAX_PLUG_NAME);
//  m_dispatch(m_plugin, effGetParamDisplay, index, 0, &pname, 0.0f);
  debug(LOG_INFO, "Setting parameter %d to %f", index, value);
  m_plugin->setParameter(m_plugin, index, value);
  return true;
}

bool vstLoader::setPath(const char *fname)
{
  struct stat s;
  char tmp_path[MAX_PATH_SIZE];
  
#if MAC
  // First, see if it's a full system path
  if(!stat(fname, &s))
  {
    if(fname[0] == '/')
    {
      strncpy(m_path, fname, MAX_PATH_SIZE);
    }
    else
    {
      char *system = new char[MAX_PATH_SIZE];
      getcwd(system, MAX_PATH_SIZE);
      snprintf(m_path, MAX_PATH_SIZE, "%s/%s", system, fname);
    }
  }
  else
  {
    // Then check the global VST directory
    snprintf(tmp_path, MAX_PATH_SIZE, "%c%s%c%s", DEF_DIR_DELIMITER, DEF_VST_PATH, DEF_DIR_DELIMITER, fname);
    if(!stat(tmp_path, &s))
    {
      strncpy(m_path, tmp_path, MAX_PATH_SIZE);
    }
    else
    {
      // Try same path with .vst extension
      strcat(tmp_path, ".vst");
      if(!stat(tmp_path, &s))
      {
        strncpy(m_path, tmp_path, MAX_PATH_SIZE);
      }   
      else
      {
        // Otherwise, check the user's local VST directory
        snprintf(tmp_path, MAX_PATH_SIZE, "%s/%s/%s", getenv("HOME"), DEF_VST_PATH, fname);
        if(!stat(tmp_path, &s))
        {
          strncpy(m_path, tmp_path, MAX_PATH_SIZE);
        }
        else
        {
          // Try same path with .vst extension
          strcat(tmp_path, ".vst");
          if(!stat(tmp_path, &s))
          {
            strncpy(m_path, tmp_path, MAX_PATH_SIZE);
          }          
          else
          {
            debug(LOG_ERROR, "VST '%s' was not found", fname);
            memset(m_path, 0x0, MAX_PATH_SIZE);
            return false;
          }
        }
      }
    }
  }
#endif
#if WINDOWS
  // First check for a full path
  if(!stat(fname, &s))
  {
    strncpy(m_path, fname, MAX_PATH_SIZE);
  }
  else
  {
    _snprintf(tmp_path, MAX_PATH_SIZE, "%s%c%s", DEF_VST_PATH, DEF_DIR_DELIMITER, fname);
    if(!stat(tmp_path, &s))
    {
      strncpy(m_path, tmp_path, MAX_PATH_SIZE);
    }
    else 
    {
      // Try same path with .dll extension
      strcat(tmp_path, ".dll");
      if(!stat(tmp_path, &s))
      {
        strncpy(m_path, tmp_path, MAX_PATH_SIZE);
      }
      else
      {
        debug(LOG_ERROR, "VST '%s' was not found", fname);
        return false;
      }
    }
  }
  
#endif

  debug(LOG_INFO, "VST is located at %s", m_path);
  return true;
}

bool vstLoader::setProgram(int num)
{
  // Load up a program bank and go
  suspend();
  m_dispatch(m_plugin, effSetProgram, 0, num, NULL, 0.0f);
  char prog_name[MAX_PROG_NAME];
  memset(prog_name, 0x0, sizeof(char) * MAX_PROG_NAME);
  m_dispatch(m_plugin, effGetProgramName, 0, 0, &prog_name, 0.0f);
  debug(LOG_INFO, "Loaded program number %d (%s)", num, prog_name);
  resume();
  return true;
}

bool vstLoader::setSampleRate(float srate)
{
  suspend();
  debug(LOG_INFO, "Setting sample rate to %f", srate);
  m_dispatch(m_plugin, effSetSampleRate, 0, 0, NULL, srate);
  resume();
  return true;
}

void vstLoader::suspend()
{
  debug(LOG_INFO, "Suspending plugin");
  m_dispatch(m_plugin, effMainsChanged, 0, 0, NULL, 0.0f);
}

#endif
#endif