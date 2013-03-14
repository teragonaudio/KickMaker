/*
 *  auLoader.h - pluginCore
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
#define __auLoader_H

#ifndef __pluginLoader_H
#include "pluginLoader.h"
#endif

#ifndef __AUBase_h__
#include "AUBase.h"
#endif

#include <AudioToolbox/AudioUnitUtilities.h>

#ifndef __AUDebugDispatcher_h__
#include "AUDebugDispatcher.h"
#endif

extern "C" {
  /*! \brief Return a character string for a given AU property ID number. */
  static char* AUPropertyStr(AudioUnitPropertyID inID);
}

/*! \class auLoader
* \brief Framework for loading AU plugins.
*
* The auLoader class is designed to provide an easy framework for loading and using AU plugins.
* See the generic interface provided by the pluginLoader class for more information on usage.
*
* \note To activate support for this class, you need to include the AU source code in your project
* (or just the appropriate references to the header files), and you must also define the following
* preprocessor symbols:
* - USE_PC_AU
* - USE_PC_HOST
*/
class auLoader : public pluginLoader {
public:
  auLoader();
  ~auLoader();
  
  /*! \copydoc pluginLoader::getPluginPtr() */
  void* getPluginPtr() const;
  
  /*! \copydoc pluginLoader::initialize() */
  bool initialize();
  
  /*! \brief Called by an AU when data is requested
  * \param inRefCon A reference to the host object controlling the AU
  * \param ioActionFlags State variable for pre or post rendering
  * \param inTimeStamp Rendering timestamp
  * \param inBusNumber Bus number to be rendered
  * \param inNumFrames Number of frames in ioData
  * \param ioData Structure containing buffer lists
  *
  * You should not need to override this method.  It is used to pull the data from the ioData
  * structure and push it into the global _INPUTS array.
  */
  static OSStatus inputCallback(void *inRefCon,
                                AudioUnitRenderActionFlags *ioActionFlags,
                                const AudioTimeStamp *inTimeStamp,
                                UInt32 inBusNumber,
                                UInt32 inNumFrames,
                                AudioBufferList *ioData);
  
  /*! \copydoc pluginLoader::loadPlugin() */
  bool loadPlugin();
    
  /*! \brief Print out information about the plugin
    *
    * For AU plugins, information about standard AU properties, and the plugin's parameter
    * list is printed to standard output.
    */
  void printInfo() const;
  
  /*! \brief Print information about a single property
    * \param property The property number
    *
    * This method is used by printInfo()
    */
  void printInfoSingle(UInt32 property) const;
  
  /*! \copydoc pluginLoader::process() */
  void process(float **inputs, float **outputs, long frames);
  
  /*! \copydoc pluginLoader::processMidi() */
  void processMidi(int type, int byte1, int byte2, long frames);

  /*! \brief Called by an AU during pre and post rendering
    * \param inRefCon A reference to the host object controlling the AU
    * \param ioActionFlags State variable for pre or post rendering
    * \param inTimeStamp Rendering timestamp
    * \param inBusNumber Bus number to be rendered
    * \param inNumFrames Number of frames in ioData
    * \param ioData Structure containing buffer lists
    *
    * You should not need to override this method.  It is called by the AU directly before
    * and after rendering is performed.
    */
  static OSStatus renderNotify(void *inRefCon,
                               AudioUnitRenderActionFlags *ioActionFlags,
                               const AudioTimeStamp *inTimeStamp,
                               UInt32 inBusNumber,
                               UInt32 inNumFrames,
                               AudioBufferList *ioData);
  
  /*! \copydoc pluginLoader::resume() */
  void resume();
  
  /*! \copydoc pluginLoader::setBlocksize() */
  bool setBlocksize(int bsize);
  
  /*! \copydoc pluginLoader::setParameter() */
  bool setParameter(int index, float value, long frames = 0);
  
  /*! \brief Locate a plugin in the user's system
    * \param fname A string in the form type:subtype:manuf (must be colon-delimited)
    *
    * Since AU's are not loaded by an absolute path, the four-character code for the type,
    * subtype, and manufacturer must be used instead.  This information can be found in the
    * output of "auval -a".
    */
  bool setPath(const char *fname);
  
  /*! \brief Tell the plugin to load a program
    * \param num The program number
    *
    * Since Audio Units don't load reference presets by index number, this method is unused
    * for this implementation.
    */
  bool setProgram(int num);
  
  /*! \copydoc pluginLoader::setSampleRate() */
  bool setSampleRate(float srate);
  
  /*! \copydoc pluginLoader::suspend() */
  void suspend();

protected:
  /*! Processing buffer list used by the plugin. */
  AudioBufferList *m_buffer_list;
  /*! Reference to hosted plugin. */
  AudioUnit m_plugin;
  /*! Used during plugin rendering. */
  AudioTimeStamp m_time;
  /*! Used to store and locate an AU plugin. */
  ComponentDescription m_desc;
  /*! Four character code for the plugin type (normally aumu or aufx, though other types also exist). */
  char m_type[5];
  /*! Four character code for the plugin subtype (set by the developer). */
  char m_subtype[5];
  /*! Four character code for the plugin's manufacturer. */
  char m_manuf[5];

private:
};

#endif
#endif
#endif