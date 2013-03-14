/*
 *  pluginLoader.cpp - pluginCore
 *
 *  Created by Nik Reiman on 07.07.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 *  This source code may NOT be redistributed without express permission of Teragon Audio.  It may be used
 *  in free or commercial software works, but unauthorized duplication or resale in whole or part is
 *  strictly prohibited.
 */

#if USE_PC_HOST
#ifndef __pluginLoader_H
#define __pluginLoader_H

#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stack>

#if MAC
#include <Quicktime/Quicktime.h>
#endif

#ifndef __pluginCore_H
#include "pluginCore.h"
#endif

#ifndef __productDir_H
#include "productDir.h"
#endif

#if DEBUG
#if MAC
#ifndef debug
#define debug printf
#endif
#elif WIN32
#ifndef debug
#define debug OutputDebugString
#endif
#endif
#endif

#ifndef DEF_SAMPLE_RATE
/*! Default sampling rate to use for the plugin */
#define DEF_SAMPLE_RATE 44100
#endif
#ifndef DEF_BLOCKSIZE
/*! Default blocksize to use for processing */
#define DEF_BLOCKSIZE 256
#endif
#ifndef DEF_TEMPO
/*! Default tempo in beats per minute */
#define DEF_TEMPO 120
#endif
#ifndef DEF_TIMESIG_DENOM
/*! Default time signature denominator (the lower value) */
#define DEF_TIMESIG_DENOM 4
#endif
#ifndef DEF_TIMESIG_NUMER
/*! Default time signature numerator (the upper value) */
#define DEF_TIMESIG_NUMER 4
#endif

#ifndef MAX_PLUG_NAME
/*! Largest size that a plugin's name can be */
#define MAX_PLUG_NAME 32
#endif
#ifndef MAX_PROG_NAME
/*! Largest size for program names */
#define MAX_PROG_NAME 32
#endif
#ifndef MAX_CHANNELS
/*! Maximum number of processing channels */
#define MAX_CHANNELS 2
#endif

/*! Structure containing information about a parameter */
typedef struct
{
  /*! Parameter index */
  int index;
  /*! Parameter value */
  float value;
} tPluginParameter;

/*! \class pluginLoader
* \brief Generic interface for loading and processing data with a plugin
*
* This class provides the basic functions used by the auLoader and vstLoader classes, which include
* loading and initializing a plugin, processing data, sending MIDI and parameter change events, and
* retreiving basic information about the plugin.
*
* \note To enable support for loading plugins in your project, you must define the following preprocessor
* symbols:
* - USE_PC_HOST
*/
class pluginLoader
{
public:
  pluginLoader();
  ~pluginLoader();
  
#if MAC
  /*! Return a FSSpec reference to the path of the plugin (used in Mac OSX only) */
  const FSSpec getFSSpec() const;
#endif
  
  /*! Return the plugin's name */
  const char* getName() const;
  
  /*! Number of indexed parameter */
  virtual int getNumParameters() const { return -1; };
  
  /*! Get the value of a particular parameter */
  virtual float getParameter(int index) const { return 0.0f; };
  
  /*! Return the absolute path of the plugin */
  const char* getPath() const;
  
  /*! Return a pointer to the plugin */
  virtual void* getPluginPtr() const;
  
  /*! Find and load the plugin into memory */
  virtual bool loadPlugin() = 0;
  
  /*! Prepare the plugin to begin processing */
  virtual bool initialize() = 0;
    
  /*! \brief Print some information about the plugin
    *
    * Depending on the plugin type, you may choose to print out different types of information.
    * This method is strictly optional, and is only used for debugging purposes.
    */
  virtual void printInfo() const {};
  
  /*! \brief Process a data chunk
    * \param inputs Array of floating point data for input
    * \param outputs Array where output should be stored
    * \param frames Number of frames in the chunk
    */
  virtual void process(float **inputs, float **outputs, long frames) = 0;
  
  /*! \brief Send a MIDI event to the plugin
    * \param type The first byte to determine the MIDI message type
    * \param byte1 The first data byte in the MIDI message
    * \param byte2 The second data byte in the MIDI message
    * \param frames Number of frames to schedule the event
    */
  virtual void processMidi(int type, int byte1, int byte2, long frames) = 0;

  /*! Resume the plugin to continue processing input */
  virtual void resume() {};
  
  /*! \brief Set the number of active channels
    * \param num_channels The number of channels to use (must be less than or equal to MAX_CHANNELS)
    */
  virtual bool setChannels(int num_channels);
  
  /*! \brief Set the plugin's name.
    *
    * When no name is provided, then the plugin's name will be automatically determined from the
    * plugin's pathname.
    */
  virtual void setName();
  
  /*! \brief Set the plugin's name
    * \param name The name of the plugin to use (will be directly copied into m_name)
    */
  virtual void setName(const char *name);
  
  /*! \brief Set a parameter within the plugin
    * \param index The parameter index to set
    * \param value The value which the parameter should be set to
    * \param frames The number of frames to schedule the parameter change
    */
  virtual bool setParameter(int index, float value, long frames = 0);
  
  /*! \brief Set the path of the plugin
    * \param fname The path of the plugin.  The nature of this variable is implementation-specific.
    */
  virtual bool setPath(const char *fname);
  
  /*! \brief Load a program within the plugin
    * \param num The program number to load
    *
    * This method was provided primarily for the VST plugin architecture, as AU plugins do not really
    * have a concept of program numbers.
    */
  virtual bool setProgram(int num);
  
  /*! \brief Set the blocksize for the plugin
    * \param bsize The new blocksize to use (in frames)
    *
    * This method should be called before any calls to process().
    */
  virtual bool setBlocksize(int bsize);
  
  /*! \brief Set the sample rate for the plugin
    * \param srate The sample rate in Hertz
    */
  virtual bool setSampleRate(float srate);
  
  /*! Suspend the plugin from processing input */
  virtual void suspend() {};
  
protected:
  /*! Flag set to determine whether plugin has been loaded successfully. */
  bool m_loaded;
  /*! The display name of the plugin */
  char m_name[MAX_PLUG_NAME];
  /*! Absolute path where the plugin is located */
  char m_path[MAX_PATH_SIZE];
  /*! Number of channels for processing */
  int m_num_channels;
private:
};

#endif
#endif