/*
 *  vstLoader.h
 *  MissWatson
 *
 *  Created by Nik Reiman on 23.07.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#if USE_PC_VST
#if USE_PC_HOST

#ifndef __vstLoader_H
#define __vstLoader_H

#if USE_PC_MIDI
#if MAC
#include "CoreMIDI/MIDIServices.h"
#endif
#endif

#ifndef __pluginLoader_H
#include "pluginLoader.h"
#endif

#ifndef __audioeffectx__
#include "audioeffectx.h"
#endif

#if MAC
#define DEF_VST_PATH "Library/Audio/Plug-Ins/VST"
#endif
#if WINDOWS
#define DEF_VST_PATH "C:\\Program Files\\Steinberg\\VstPlugins"
#endif

#if USE_PC_MIDI
#if MAC
#define MAX_DEV_NAME 32

typedef struct {
  char devicename[MAX_DEV_NAME];
  int portnumber;
  MIDIEntityRef entity;
} tMidiPort;

#endif
#endif

// VST callback functions
extern "C" {
  VstIntPtr VSTCALLBACK host(AEffect *effect, VstInt32 opcode, VstInt32 index,
                             VstInt32 value, void *ptr, float opt);
}

typedef AEffect *(*vstPluginFuncPtr)(audioMasterCallback host);
typedef VstIntPtr (*dispatcherFuncPtr)(AEffect *effect, VstInt32 opCode, VstInt32 index,
                                       VstInt32 value, void *ptr, float opt);
typedef float (*getParameterFuncPtr)(AEffect *effect, VstInt32 index);
typedef VstInt32 (*processEventsFuncPtr)(VstEvents *events);
typedef void (*processFuncPtr)(AEffect *effect, float **inputs, float **outputs, VstInt32 sampleFrames);
typedef void (*setParameterFuncPtr)(AEffect *effect, VstInt32 index, float value);

// C callback functions
void *openEditor(void *e);
#if USE_PC_MIDI
void scanMidi();
#endif

/*! \class vstLoader
* \brief Framework for loading VST plugins.
*
* The vstLoader class is designed to provide an easy framework for loading and using VST 2.4 plugins.
* See the generic interface provided by the pluginLoader class for more information on usage.
*
* \note To activate support for this class, you need to include the VST source code in your project
* (or just the appropriate references to the header files), and you must also define the following
* preprocessor symbols:
* - USE_PC_VST
* - USE_PC_HOST
*/
class vstLoader : public pluginLoader {
public:
  vstLoader();
  ~vstLoader();
  
  /*! \copydoc pluginLoader::getPluginPtr() */
  void* getPluginPtr() const;
  
  int getNumParameters() const;
  float getParameter(int index) const;
  
  /*! \brief Load the plugin based on the information in m_path.  Under Mac OSX, the loadBundlePlugin()
  * method will be called first, and if this call fails, then loadCFMPlugin().
  */
  bool loadPlugin();
  
#if MAC
  /*! Attempt to load a Mach-O plugin from a bundle */
  bool loadBundlePlugin();
  
  /*! Attempt to load a classic CFM plugin */
  bool loadCFMPlugin();
#endif
  
#if WINDOWS
  /*! Load a plugin from a DLL file */
  bool loadDLLPlugin();
#endif
  
  /*! \copydoc pluginLoader::initialize() */
  bool initialize();
  
  /*! Print some information about the plugin.  This includes the VST capabilities, and the names and
  * indexes of all parameters and programs. */
  void printInfo() const;
  
  /*! \copydoc pluginLoader::process() */
  void process(float **inputs, float **outputs, long frames);
  
  /*! \copydoc pluginLoader::processMidi() */
  void processMidi(int type, int byte1, int byte2, long frames = 0);

#if MAC
  /*! Create and return a CFM-style pointer to the plugin.  Used by loadCFMPlugin(). */
  void* makeCFMPtr(void *addr);
  /*! Create and return a pointer to a Mach-O plugin.  Used by loadBundlePlugin(). */
  void* makeMachOPtr(void *cfmfp);
#endif
  
  /*! \copydoc pluginLoader::resume() */
  void resume();
  
  /*! \copydoc pluginLoader::setParameter() */
  bool setParameter(int index, float value, long frames = 0);
  
  /*! \brief Search for a plugin and resolve its system path
  * \param fname The plugin name or path to a plugin
  *
  * Under Mac OSX, this class will search for the plugin in the following order:
  * - A full system path
  * - The name of a plugin located in the global VST directory, /Library/Audio/Plug-Ins/VST
  * - The name of a plugin located in the user's VST directory, ~/Library/Audio/Plug-Ins/VST
  *
  * Under Windows, this class will search for the plugin in the following order:
  * - A full system path to a DLL
  * - The name of a plugin located in C:\\Program Files\\Steinberg\\VSTPlugins
  *
  * Unfortunately, the VST specifications don't provide a reliable way to locate plugins under
  * Windows, so only this hardcoded path is used.  Use of full system paths is therefore encouraged.
  * Also, when not using a full path, the ".vst" or ".dll" extension may be omitted
  */
  bool setPath(const char *fname);
  
  /*! \brief Load a program in the VST
  * \param num The program number.  No checks are done to ensure that this is a valid program number.
  */
  bool setProgram(int num);
  
  /*! \copydoc pluginLoader::setBlocksize() */
  bool setBlocksize(int bsize);
  
  /*! \copydoc pluginLoader::setSampleRate() */
  bool setSampleRate(float srate);
  
  /*! \copydoc pluginLoader::suspend() */
  void suspend();
  
protected:
  /*! Pointer to the actual plugin */
  AEffect *m_plugin;
  /*! Dispatch wrapper variable */
  dispatcherFuncPtr m_dispatch;
  /*! Pointer to the host callback function */
  audioMasterCallback m_host_ptr;
  
private:
};

#endif
#endif
#endif