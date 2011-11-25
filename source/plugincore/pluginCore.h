/*
 *  pluginCore.h - pluginCore
 *
 *  Created by Nik Reiman on 27.12.05.
 *  Copyright 2005 Teragon Audio. All rights reserved.
 *
 *  This source code may NOT be redistributed without express permission of Teragon Audio.  It may be used
 *  in free or commercial software works, but unauthorized duplication or resale in whole or part is
 *  strictly prohibited.
 */

#ifndef __pluginCore_H
#define __pluginCore_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>
#include <vector>
#include <typeinfo>

#if MAC
#include <Carbon/Carbon.h>
#include <sys/types.h>
#include <dirent.h>
#endif

#if WINDOWS
#include <Windows.h>
#endif

#if USE_PC_AU
#include <AudioToolbox/AudioUnitUtilities.h>
#include "AUScopeElement.h"
#include "AUBase.h"
#include "AUEffectBase.h"
#endif

#if USE_PC_EVENTS
#ifndef __eventManager_H
#include "eventManager.h"
#endif
#endif

#if USE_PC_LOGGER
#ifndef __xmlLogger_H
#include "xmlLogger.h"
#endif
#endif

#ifndef __productDir_H
#include "productDir.h"
#endif

#ifndef __xmlLogger_H
#include "xmlLogger.h"
#endif

#if USE_PC_PRESET
#ifndef Expat_INCLUDED
#include "expat.h"
#endif
#endif

// Preprocessor definitions /////////////////////////////////////////////////////////

#if WIN32
#ifndef XMLCALL
#define XMLCALL __cdecl
#endif
#define unlink remove
#endif

#if MAC
#ifndef DEF_DIR_DELIMITER
/*! Directory delimiter for mac */
#define DEF_DIR_DELIMITER '/'
#endif
#ifndef DEF_DIR_ROOT
/*! Topmost directory */
#define DEF_DIR_ROOT "/"
#endif
#endif

#if WIN32
#ifndef DEF_DIR_DELIMITER
/*! Directory delimiter for windows */
#define DEF_DIR_DELIMITER (char)92
#endif
#ifndef DEF_DIR_ROOT
/*! Topmost directory */
#define DEF_DIR_ROOT "C:\\"
#endif
#endif

#ifndef DEF_DC_OFFSET
/*! Used to prevent math errors, division by 0, etc. */
#define DEF_DC_OFFSET 1E-25f
#endif
#ifndef DEF_TUNING
/*! Default tuning.  This is only used for instrument plugins */
#define DEF_TUNING 440.0
#endif
#ifndef DEF_PRESET_EXTENSION
/*! What file extension to use for presets */
#define DEF_PRESET_EXTENSION ".xml"
#endif
#ifndef DEF_BANK_TAG
/*! Used in preset files for the XML bank tag name */
#define DEF_BANK_TAG "bank"
#endif
#ifndef DEF_PRESET_TAG
/*! Used in preset files for the XML preset tag name */
#define DEF_PRESET_TAG "preset"
#endif
#ifndef DEF_PARAMETER_TAG
/*! Used in preset files for the XML parameter tag name */
#define DEF_PARAMETER_TAG "parameter"
#endif
#ifndef DEF_HIDDEN_PARAM_NAME
/*! What label to use for locked parameters (applies to non-debug builds only) */
#define DEF_HIDDEN_PARAM_NAME "(Hidden)"
#endif
#ifndef DEF_REPLACEMENT_DELIMITER
/*! What character should replace DEF_PRESET_DELIMITER should it be found in the preset
data.  For user strings inside of chunked data, this replacement will not be performed. */
#define DEF_REPLACEMENT_DELIMITER '-'
#endif
#ifndef DEF_PRESET_BANK_TYPE
/*! Used in plugin state info as the IFF chunk name for the current preset bank */
#define DEF_PRESET_BANK_TYPE "PREB"
#endif
#ifndef DEF_PRESET_NAME_TYPE
/*! Used in plugin state info as the IFF chunk name for the current preset name */
#define DEF_PRESET_NAME_TYPE "PREN"
#endif
#ifndef DEF_PARAM_TYPE
/*! Used in plugin state info as the IFF chunk name for a parameter */
#define DEF_PARAM_TYPE "PARM"
#endif
#ifndef MAX_NAME
/*! Maximum length of a parameter name */
#define MAX_NAME 24
#endif
#ifndef MAX_PATH_SIZE
/*! Maximum length for file pathnames */
#define MAX_PATH_SIZE 384
#endif
/*! Number of frequencies in the frequency table, which corresponds to the number of defined MIDI notes. */
#define NUM_MIDI_NOTES 128

// Used by expat for reading presets
#if USE_PC_PRESET
#ifdef XML_LARGE_SIZE
#if defined(XML_USE_MSC_EXTENSIONS) && _MSC_VER < 1400
#define XML_FMT_INT_MOD "I64"
#else
#define XML_FMT_INT_MOD "ll"
#endif
#else
#define XML_FMT_INT_MOD "l"
#endif
#endif

#ifndef USE_PC_AU
#define kAudioUnitParameterUnit_AbsoluteCents -1
#define kAudioUnitParameterUnit_BPM -1
#define kAudioUnitParameterUnit_Beats -1
#define kAudioUnitParameterUnit_Boolean -1
#define kAudioUnitParameterUnit_Cents -1
#define kAudioUnitParameterUnit_CustomUnit -1
#define kAudioUnitParameterUnit_Decibels -1
#define kAudioUnitParameterUnit_Degrees -1
#define kAudioUnitParameterUnit_EqualPowerCrossfade -1
#define kAudioUnitParameterUnit_Generic -1
#define kAudioUnitParameterUnit_Hertz -1
#define kAudioUnitParameterUnit_Indexed -1
#define kAudioUnitParameterUnit_LinearGain -1
#define kAudioUnitParameterUnit_MIDIController -1
#define kAudioUnitParameterUnit_MIDINoteNumber -1
#define kAudioUnitParameterUnit_Meters -1
#define kAudioUnitParameterUnit_Milliseconds -1
#define kAudioUnitParameterUnit_MixerFaderCurve1 -1
#define kAudioUnitParameterUnit_Octaves -1
#define kAudioUnitParameterUnit_Pan -1
#define kAudioUnitParameterUnit_Percent -1
#define kAudioUnitParameterUnit_Phase -1
#define kAudioUnitParameterUnit_Rate -1
#define kAudioUnitParameterUnit_Ratio -1
#define kAudioUnitParameterUnit_RelativeSemiTones -1
#define kAudioUnitParameterUnit_SampleFrames -1
#define kAudioUnitParameterUnit_Seconds -1
#endif

// Preprocessor function macros /////////////////////////////////////////////////////////

/*! Provides quick access to a parameter's value */
#define PARAM(x) ( m_params[x].value )

/*! Convert linear value to decibels */
#define LIN2DB(x) ( log(x) * 8.6858896380650365530225783783321 )

/*! Convert decibels to linear scale */
#define DB2LIN(x) ( exp(x * 0.11512925464970228420089957273422) )

/*! Convert a four character string to a FourCC (aka OSType), a 4-byte quantity */
#define STR2FOURCC(x) ( (unsigned int)((x[0] << 24) | (x[1] << 16) | (x[2] << 8) | x[3]) )

/*! Compatibility redefinition for legacy PluginCore-v1 code */
#define setParameterNormalized setParameterScaled

/*! Compatibility redefinition for legacy PluginCore-v1 code */
#define getParameterNormalized getParameterScaled

// Enumerated types /////////////////////////////////////////////////////////////////////

/*! These are used by the event handling subsystem of pluginCore, which is used to handle
frame offsets for MIDI note and parameter changes. */
enum DEF_EVENT_TYPES
{
  /*! Indicates that the event is for a parameter change */
  EVT_ACTION_PARAM = 0,
  /*! Used for MIDI messages */
  EVT_ACTION_MIDI,
  /*! All other events (ie, user-defined stuff) */
  EVT_ACTION_OTHER
};

/*! Different types of requests recognized by getParameter(). */
enum DEF_REQUEST_TYPES
{
  /*! Request the display string for a parameter.  This will be a formatted number string,
  except in the case of boolean parameters, in which the strings "On" and "Off" are used */
  REQ_DISPLAY = 0,
  /*! Request the parameter's name */
  REQ_NAME,
  /*! Request the parameter's label.  For Audio Units, this will return a floating point value.
  For VST's, a string is stored in the character string parameter passed into getParameter() */
  REQ_LABEL,
  /*! Request the value of a parameter.  For VST's, this will be a normalized floating point value
  between {0.0, 1.0}. */
  REQ_VALUE,
  /*! Request the raw value of the parameter (ie, the actual value).  Use the PARAM macro for
  fast access to this data from within the pluginCore object. */
  REQ_VALUE_RAW,
  /*! Request the minimum value of the parameter */
  REQ_VALUE_MIN,
  /*! Request the maximum value of the parameter */
  REQ_VALUE_MAX,
  /*! Request the initial value that this parameter was initialized to */
  REQ_VALUE_DEF,
  /*! Request the unit label string */
  REQ_LABEL_STR,
  /*! Request for associated chunked parameter data */
  REQ_CHUNK,
  /*! Request the size for a parameter's chunked data, in bytes */
  REQ_CHUNK_SIZE
};

/*! When creating a new parameter with the addParameter() call, one of these types must be used to
determine how the parameter will be displayed.  Internally, there is little difference in how the types
are treated, but there is some difference as to how pluginCore interacts with the host's parameter request
calls depending on which type is used.

\note For a regular, floating point parameter with nothing fancy, use the TYP_GENERIC type */
enum DEF_PARAM_TYPE_LABELS
{
  /*! Absolute cents */
  TYP_ABS_CENTS = 0,
  /*! Beats (musical time) */
  TYP_BEATS,
  /*! Boolean (true/false) */
  TYP_BOOL,
  /*! Beats per minute */
  TYP_BPM,
  /*! Cents */
  TYP_CENTS,
  /*! User-defined */
  TYP_CUSTOM,
  /*! Decibels (see the pluginCore::LIN2DB and pluginCore::DB2LIN macros for quick conversions) */
  TYP_DB,
  /*! Degrees */
  TYP_DEG,
  /*! Crossfade amount */
  TYP_EQ_XFADE,
  /*! <b>A normal, floating-point parameter</b> */
  TYP_GENERIC,
  /*! Frequency in Hertz */
  TYP_HZ,
  /*! Indexed (unused) */
  TYP_INDEXED,
  /*! Linear (unused) */
  TYP_LINEAR,
  /*! MIDI controller number (unused) */
  TYP_MIDI_CONTROLLER,
  /*! MIDI note number (unused) */
  TYP_MIDI_NOTE,
  /*! Meters */
  TYP_METERS,
  /*! Milliseconds */
  TYP_MILLISECONDS,
  /*! Crossfader curve types */
  TYP_FADER_CURVE,
  /*! Octaves */
  TYP_OCTAVES,
  /*! Panning amount */
  TYP_PAN,
  /*! Percent (floating point quantity) */
  TYP_PERCENT,
  /*! Phase */
  TYP_PHASE,
  /*! Rate of change */
  TYP_RATE,
  /*! Ratio */
  TYP_RATIO,
  /*! Relative semitones */
  TYP_RELATIVE_SEMITONES,
  /*! Frames (integer quantity) */
  TYP_SAMPLEFRAMES,
  /*! Seconds */
  TYP_SECONDS,
  /*! Same as TYP_HZ, but will automatically use logarithmic scales in getParameter() calls */
  TYP_HZ_LOG,
};

// Type structures //////////////////////////////////////////////////////////////////////

/*! Parameter label structure.  This is basically just used to store the actual label string
and the corresponding index number for the pluginCore::DEF_PARAM_TYPE_LABELS enumeration */
typedef struct
{
  const int aucode;
  const char *label;
} tLabel;

/*! Structure for a generic MIDI message. */
typedef struct
{
  /*! Status byte */
  int status;
  /*! MIDI channel */
  int channel;
  /*! First data byte */
  int byte1;
  /*! Second data byte */
  int byte2;
  /*! Unused */
  long reserved;
} tMidiMessage;

/*! This structure actually holds all of the data associated with a given parameter. */
typedef struct
{
  /*! The parameter type (see pluginCore::DEF_PARAM_TYPE) */
  int type;
  /*! Parameter index number */
  int index;
  /*! Display name */
  char name[MAX_NAME];
  /*! Actual value */
  float value;
  /*! The minimum permissible value set during addParameter() */
  float minval;
  /*! The maximum permissible value set during addParameter() */
  float maxval;
  /*! The initial value set during addParameter() */
  float defval;
  /*! Associated chunked data for the parameter (will be a null pointer by default) */
  void *chunk;
  /*! Number of bytes in the chuck */
  int chunk_size;
  /*! True if parameter is locked, false otherwise */
  bool lock;
} tParam;

/*! Used by the core's messaging and event handling system. */
typedef struct
{
  /*! Event type (see pluginCore::DEF_EVENT_TYPES) */
  int action;
  
  union
  {
    /*! Parameter data, in the event of a parameter change */
    tParam param_data;
    /*! MIDI event data */
    tMidiMessage midi_data;
  } data;
} tCoreEvent;

/*! Used to store plugin state information */
typedef struct
{
  /*! Chunk type */
  unsigned int type;
  /*! Length (in bytes) */
  unsigned int length;
  /*! Associated floating point value used for parameter storage */
  float value;
} tIFFChunk;

class pluginCore
#if USE_PC_EVENTS
: public eventListener
#endif
{
public:
  /*! \brief Create a new pluginCore instance
  * \param num_params Number of parameters for the plugin
  * \param version Plugin version, used for preset writing
  * \param name The Plugin's name
  * \param logfile The absolute path for a logfile, if using logging capabilities
  * See the documentation for the xmlLogger class for more details on this.  If using
  * logging, this field may be left blank, in which case a file on the user's desktop
  * with the name of XML_LOGGER_DEFAULT_NAME will be used (if it exists).
  * \param logmode Either XML_WRITER_MODE_APPEND or XML_WRITER_MODE_WRITE
  */
  pluginCore(int num_params = 0, long version = 1000, const char *name = NULL,
             char *logfile = NULL, int logmode = XML_WRITER_MODE_APPEND);

  virtual ~pluginCore();
  
  /*! \brief Configures a parameter
  * \param index The index of the parameter
  * \param display The parameter's name
  * \param type Parameter type (see pluginCore::DEF_PARAM_TYPE_LABELS)
  * \param minval Minimum value for the parameter
  * \param maxval Maximum value for the parameter
  * \param initval Initial value that should be used
  * \param lock True if the parameter should be "locked", false (or omitted) otherwise
  * \param size Number of bytes to allocate for chunked parameters
  *
  * Adds a parameter to the array of parameters managed by the plugin.  Note that the number
  * of parameters is actually determined upon initialization of the pluginCore object, and
  * attempting to add more parameters than allocated will cause problems.
  *
  * Also, pluginCore uses "locked" parameters, which provide a mechanism for the external
  * plugin interface to communicate with the pluginCore object.  To set a locked parameter,
  * one must explicitly call setParameter() with the override flag set to true.
  * This makes it possible for the programmer to set parameters from within the plugin-specific
  * framework.  Although these parameters will show up in parameter lists, their value cannot be
  * altered by the user, which makes for a convenient way of passing information between the plugin
  * shell and core.  For example, a plugin might want to store the sample rate of the host as a
  * parameter, rather than continuously polling for it during CPU-intensive operations.  So, by
  * setting this parameter as being "locked", the programmer can explicitly set it's value upon
  * plugin initialization, but the user will not be able to alter it.  However, the parameter
  * \b will be visible to the user, and in non-debug builds, it will have a display name of
  * DEF_HIDDEN_PARAM_NAME.
  *
  * \note Due to the way that Audio Unit parameters are displayed, locked parameters may appear
  * to be modifiable by the user.  However, any value changes to these parameters are ignored.
  *
  * Each parameter may also have a "chunk" associated with it, which is convenient for storing
  * strings or other types of user data.  For more information, see the documentation for
  * setParameter(int index, void *chunk, int chunk_size, bool override).
  */
  void addParameter(int index, const char *display, int type = TYP_GENERIC,
                    float minval = 0.0, float maxval = 1.0, float initval = 0.0,
                    bool lock = false, int size = 0);
  
  /*! \brief Returns a parameter property
  * \param request The request type (see pluginCore::DEF_REQUEST_TYPES)
  * \param index The parameter index that is being requested
  * \param sdata Pre-allocated memory to store non-numerical properties, including:
  * - REQ_NAME
  * - REQ_LABEL_STR
  * - REQ_DISPLAY
  * - REQ_CHUNK
  * For queries that do not involve parameter properties (such as the parameter's value), this can
  * safely be set to NULL.  When used, a 32 character buffer is recommended for strings.  For chunked
  * data, the size of the data should be first retrieved by calling this method with REQ_CHUNK_SIZE.
  * \return The value/property of the parameter (when requested), -1.0 on error, 0.0 otherwise.
  *
  * For fast access to a parameter's floating point value, use the pluginCore::PARAM macro.  For
  * Audio Units, REQ_VALUE and REQ_VALUE_RAW both return the actual value of the parameter.  For
  * VST's, REQ_VALUE will return the \b scaled value of the parameter, which is a floating
  * point value between 0.0 and 1.0.  To get the actual value, use REQ_VALUE_RAW instead.
  *
  * For locked parameters, the parameter name will be followed by an asterix ("*") to indicate the
  * parameter is locked.
  */
  virtual float getParameter(int request, int index, void *sdata = NULL) const;
  
  /*! \brief Return the scaled value in the range 0.0 - 1.0
  * \param index The parameter index to retrieve
  *
  * There are some times when one needs the "raw" parameter value, but cannot get it through
  * pluginCore itself.  The primary example of this is using VSTGUI components from an AU.  With Audio
  * Units, parameter are stored internally with their actual value, rather than a number in the
  * range { 0.0, 1.0 } as is the custom with VST's.  So, for a VST plugin, the call to getParameter()
  * with REQ_VALUE will return a value in this range, but for AU's, it will return the actual
  * value of the parameter.  When using UI components which are expecting a value in the range
  * of { 0.0, 1.0 }, this can be problematic, so this conversion function was added.
  *
  * You should use the regular getParameter() calls within the plugin, but you might have to use
  * this function to help out with GUI stuff.
  */
  virtual float getParameterScaled(int index) const;
  
  /*! \brief Dumps plugin state information for the host to save
  * \param bytes Pointer to an integer which will hold the number of bytes counted
  * \return A pointer to a memory block with the current state IFF data
  *
  * In order to properly save the plugin state, hosts will provide a plugin with an opportunity
  * to save state data in a memory block which will be given to the plug upon initialization in
  * the restoreState() method.
  *
  * Presently, PluginCore preserves the following information in the plugin state:
  * - Current preset bank name (if built with preset support)
  * - Current preset number (if built with preset support)
  * - Each parameter's value and any chunked information associated with this parameter
  *
  * This procedure is a two-part operation; first, the sizes of all chunks are gathered,
  * allowing proper allocation of memory pointed to by userData.  After this, the actual data is
  * written in IFF format to memory, with the first four bytes representing the floating point value,
  * and the remaining being chunk data.
  */
  virtual unsigned char* getState(int &bytes);
  
  /*! \brief Return the plugin's version.
  * \return Version number of the plugin
  *
  * By default, the plugin version is set to 1000.  The only place that this is actually used is in
  * the preset subsystem to determine which version of the plugin made a given preset */
  virtual long getVersion() const;
  
#if USE_PC_EVENTS
  /*! \brief Event handling method used by pluginCore objects
  * \param data Actually a pointer to a tCoreEvent structure
  *
  * Some hosts prefer to send MIDI and/or parameter changes to plugins with a frame offset.  This means
  * that although the event was actually received by the plugin, it is not to actually process it until
  * it has processed a certain number of frames.  To deal with this, pluginCore uses an eventManager
  * object with a sample frames clock.  So, if you want sample-accurate event handling, you must not only
  * include the eventManager classes in your code, but you must also call process() from your process()
  * override.  This will keep the plugin's clock running and make sure that events happen on time.
  */
  virtual void handleEvent(void *data = 0);
#endif
  
  /*! \brief Manually lock or unlock a parameter
  * \param index The parameter to modify
  * \param lock True for locked, false for unlocked
  */
  void lockParameter(int index, bool lock = true);
  
  /*! \brief Core processing method
  * \param inputs Array of floating point arrays for the input stream
  * \param outputs Array of floating point arrays for the output stream
  * \param frames Number of frames to process
  *
  * This method is called to process the actual data by the plugin.  Its structure is based off of
  * the VST process method, and it expects data to be passed in the same way.  For plugin API's such
  * as the Audio Unit v1 specification, interlaced data is used, while in VST (and AudioUnits v2), separate
  * buffers of non-interlaced data are used.  Ultimately, it is up to you how to handle this data,
  * but the recommended method is to use separate buffers with non-interlaced data.
  *
  * This process method doesn't actually do anything, but it should be called from your inherited class
  * to keep the event clock updated.
  */
  virtual void process(float **inputs, float **outputs, long frames);
  
  /*! \brief Overridable method for plugin reset */
  virtual void reset();
  
  /*! \brief Sets a parameter value
  * \param index The parameter to set
  * \param value The value the parameter should be set to
  * \param override Set to true to override the lock on a locked parameter
  * \param frames Offset in frames (not supported by all hosts)
  *
  * With VST's, this method will automatically detect if a raw or scaled value is being passed in.
  * A VST host should pass in scaled values in the range of {0.0, 1.0}.  However, in the case of
  * locked parameters, the programmer often expects to simply pass in the value that they wish the
  * parameter to be set to.  For this reason, any value greater than 1.0 passed into this function
  * will be directly stored into the parameter's value.  Scaled values will instead by calculated
  * to reflect a value inbetween the minimum and maximum range, which are set when adding the parameter.
  *
  * To set a locked parameter, the "override" parameter \b must be set to true.  Otherwise, the
  * request will be ignored.
  */
  virtual bool setParameter(int index, float value, bool override = false, long frames = 0);
  
  /*! \brief Sets chunked data for a parameter
  * \param index The parameter index to set
  * \param *chunk The data to set.
  * \param chunk_size The number of bytes in chunk
  * \param override Manually override the lock on a locked parameter
  * \param frames Offset in frames (not supported by all hosts)
  * \return true on success, false if an error is encountered
  */
  virtual bool setParameter(int index, void *chunk, int chunk_size, bool override = false, long frames = 0);
  
  /*! \brief Sets a parameter's actual value from a number in the range { 0.0, 1.0 }
  * \param index The index number to set
  * \param value The value with range of { 0.0, 1.0 }
  * \param lock Override parameter lock
  *
  * This function is the compliment of getParameterScaled().  You should probably only have to use it from
  * UI components.
  */
  virtual bool setParameterScaled(int index, float value, bool lock = false);
  
  /*! \brief Restore the plugin's state upon initialization
  * \param userData Pointer to a chunk of memory containing IFF data
  * \param bytes Number of bytes in the chunk
  *
  * When a host wishes to close or save the current document, it should call getState() to retrieve
  * a chunk of memory which will be given to the plugin upon re-initialization.  This method takes
  * the data block and uses it to set the plugin's state.  This includes setting parameter data,
  * any chunked data associated with parameters, and the preset bank and name, if built with preset support.
  */
  virtual bool setState(unsigned char *userData, unsigned int bytes);
  
  /*! \brief Set the plugin's internal version number
  * \param version The version number
  */
  virtual void setVersion(long version = 1000);
  
#if USE_PC_PRESET
  /*! Structure for holding information about a preset */
  typedef struct
  {
    /*! Bank name */
    char bank[MAX_NAME];
    /*! Preset name */
    char name[MAX_NAME];
    /*! Number of parameters associated with the preset */
    int num_params;
    /*! The full path is used for deleting presets (when not associated with a bank) */
    char full_path[MAX_PATH_SIZE];
    /*! Parameter data */
    tParam *data;
  } tPreset;
  
  /*! \brief Adds a new preset to the preset
  * \param preset Pointer to a tPreset data structure.  This data may be freed after calling this method.
  */
  virtual void addPreset(tPreset *preset);
  
  /*! \brief Delete a preset file
  * \param name The preset name to remove
  * \param bank The bank the preset is located in
  *
  * If the preset is part of a bank, then it will only be removed from the list of presets in the plugin.
  * Otherwise, then the preset will be physically removed from disk.
  */
  virtual void deletePreset(const char *name, const char *bank = NULL);
  
  /*! \brief Delete a preset file
  * \param index The index number of the preset to remove
  *
  * If the preset is part of a bank, then it will only be removed from the list of presets in the plugin.
  * Otherwise, then the preset will be physically removed from disk.
  */
  virtual void deletePreset(int index);
  
  /*! \brief Returns the index number for a preset name
  * \param name The preset name
  * \param bank The bank the preset is located in
  */
  virtual int findPreset(const char *name, const char *bank = NULL) const;
  
  /*! \brief Get the current preset number */
  virtual int getCurrentPresetIndex() const;
  
  /*! \brief Get the current preset bank name
  * \param text Preallocated memory block (of at least MAX_NAME bytes) which the result is written to
  */
  virtual void getCurrentPresetBank(char *text) const;
  
  /*! \brief Get the current preset name
  * \param text Preallocated memory block (of at least MAX_NAME bytes) which the result is written to
  */
  virtual void getCurrentPresetName(char *text) const;
  
  /*! \brief Get the number of presets */
  virtual int getNumPresets() const;
  
  /*! \brief Get the name of a preset's bank, using a user-specified index number.
  * \param index The index number of the preset
  * \param text Preallocated memory block (of at least MAX_NAME bytes) which the result is written to
  */
  virtual void getPresetBank(int index, char *text) const;
  
  /*! \brief Get the name of a preset, using a user-specified index number.
  * \param index The index number of the preset
  * \param text Preallocated memory block (of at least MAX_NAME bytes) which the result is written to
  */
  virtual void getPresetName(int index, char *text) const;
  
  /*! \brief Load a preset into the plugin.  This will loop through all the core's parameters
  * and set them to the data from the preset file.
  * \param index The index of the preset
  */
  virtual void loadPreset(int index);
  
  /*! \brief Load a preset into the plugin.  This will loop through all the core's parameters
  * and set them to the data from the preset file.
  * \param name The preset name
  * \param bank The bank name (set to NULL for user presets)
  */
  virtual void loadPreset(const char *name, const char *bank = NULL);
  
  /*! \brief Advance to and automatically load the next preset.  This will loop around to the first
  * preset after the last one has been reached. */
  virtual void nextPreset();
  
  /*! \brief Go to and automatically load the previous preset. This will loop around to the last
  * preset after the first one has been reached. */
  virtual void prevPreset();
  
  /*! \brief Read a preset file in from disk and push it into the preset array
  * \param path The full (root) path a preset or preset bank
  */
  virtual void readPreset(const char *path);
  
  /*! \brief Dumps information from the current current parameter settings to disk
  * \param product The short product name
  * \param name The preset name (no extension)
  * \param bank The bank name for the preset (use NULL for user presets)
  */
  virtual bool savePreset(const char *product, char *name, const char *bank = NULL);
  
  /*! \brief Change the active preset bank
  * \param bank The bank name
  */
  virtual bool setPresetBank(const char *bank);
  
  /*! \brief Load all of the presets found in a given directory
  * \param path Full (root) path to directory
  * \param recursive Search recursively
  * \return Number of presets read
  */
  virtual int slurpDirectory(char *path, bool recursive = true);
  
  /*! \brief Remove special characters from a string so it is safe to use in a preset file
  * \param string The string to examine
  *
  * This method will replace all instances of "unsafe" characters with DEF_REPLACEMENT_DELIMITER.
  * "Unsafe" characters are considered to be those outside of the ranges A-Z, a-z, and 0-9.
  */
  virtual void stripSpecialChars(char *string) const;
  
  /*! \brief Callback function used by expat for reading in XML preset data */
  static void XMLCALL presetDataHandler(void *userData, const XML_Char *string, int len);
  /*! \brief Callback function used by expat for reading in XML preset data */
  static void XMLCALL presetElementStartHandler(void *userData, const char *name, const char **atts);
  /*! \brief Used by expat for reading in XML preset data */
  static void XMLCALL presetElementEndHandler(void *userData, const char *name);
#endif
  
#if USE_PC_MIDI
  /*! \brief Virtual method to be called when a MIDI CC occurs */
  virtual void controlChange(int control, int value) {};
  
  /*! \brief Virtual method to be called when a note is turned on.  You will receive notes with a velocity of 0 */
  virtual void noteOn(int note, int velocity) {};
  
  /*! \brief Virtual method to be called when a note is turned off */
  virtual void noteOff(int note) {};
  
  /*! \brief Method to which MIDI events are sent for processing.  Not necessary to override, unless you wish to
  * implement a different way of processing MIDI events.
  */
  virtual void processMidi(int status, int channel, int byte1, int byte2, long frames = 0);
  
  /*! \brief Handling for Midi Sysex (system exclusive) stuff
  * \param length The size of the sysex message
  * \param data The data payload
  *
  * When this method gets called, it will push the sysex data into the m_midi_sysex stack, where
  * it can be popped off and used.  Note that memory for the m_midi_sysex.data member is allocated
  * from the heap, so you must delete them when they are done being processed.  When such an event
  * is triggered, the sysex() method will be called.
  */
  virtual void processSysex(int length, char *data);
  
  /*! \brief Removes a note from the note vector */
  void deleteNote(int index);
  
  /*! \brief Find the index of a particular note number
  * \return The index in the note array if the note is found, -1 otherwise
  */
  int findMidiNoteIndex(int index) const;
  
  /*! \brief Return the number of notes currently being played */
  int getMidiNoteCount() const;
  
  /*! \brief Get the channel for a given note */
  int getMidiNoteChannel(int index) const;
  
  /*! \brief Get the frequency (in Hertz) for a given note */
  float getMidiNoteFreq(int index) const;
  
  /*! \brief Get the frequency (in Hertz) for a given midi note number */
  float getMidiNoteTableFreq(int note) const;
  
  /*! \brief Get the note number for a given note */
  int getMidiNoteNumber(int index) const;
  
  /*! \brief Get the reserved field for a given note */
  long getMidiNoteReserved(int index) const;
  
  /*! \brief Get the note velocity for a given note */
  int getMidiNoteVelocity(int index) const;
  
  /*! \brief Sets the reserved field of a note */
  void setMidiNoteReserved(int index, long value);
  
  /*! \brief Change the tuning scole.  This is set to 440.0Hz by default */
  virtual void setTuning(float tuning);
  
  /*! \brief Override for sysex notifications
  * \param length The number of bytes in the last message received
  * \param manf_code The first byte of the data, which will contain the manufacturer's code
  */
  virtual void sysex(int length, char manf_code) {};
  
  /*! Structure for holding a MIDI note message */
  typedef struct
  {
    /*! MIDI channel */
    int channel;
    /*! Note number */
    int number;
    /*! Note velocity */
    int velocity;
    /*! Frequency of note in Hz (see the setTuning() method) */
    float frequency;
    /*! Unused */
    long reserved;
  } tMidiNote;
  
  /*! Structure for holding MIDI sysex data */
  typedef struct
  {
    /*! Number of bytes in message */
    int length;
    /*! Data chunk */
    unsigned char *data;
  } tMidiSysex;
#endif
  
#if USE_PC_EFFECTS
  /*! effectCore needs access to m_params */
  friend class effectCore;
#endif
  
protected:
  /*! Array holding all parameters for the plugin */
  tParam *m_params;
  /*! Number of parameters for the plugin */
  int m_num_params;
  /*! Version number of plugin.  Used for preset writing and a few other small things */
  long m_version;
  /*! Plugin display name */
  char m_name[MAX_NAME];
  /*! Logging device.  If USE_PC_LOGGER is not defined, then logging calls within this object
  * will be automatically cleaned up during compilation. */
  xmlLogger *m_logger;
  
#if USE_PC_PRESET
  /*! Structure holding all presets */
  std::vector<tPreset> m_presets;
  /*! Number of presets for the plugin */
  int m_num_presets;
  /*! Current preset number */
  int m_cur_preset;
#endif
  
#if USE_PC_MIDI
  /*! Currently active MIDI notes */
  std::vector<tMidiNote> m_midi_notes;
  /*! Stack of pending MIDI CC messages */
  std::stack<tMidiMessage> m_midi_ccs;
  /*! Stack of pending MIDI sysex messages */
  std::stack<tMidiSysex> m_midi_sysex;
  
  /*! Stores all of the frequencies from the tuning scale */
  float m_freq_table[NUM_MIDI_NOTES];
  /*! Number of active notes */
  int m_midi_note_count;
  /*! Used for midi learn */
  int m_midi_learn;
#endif
  
#if USE_PC_EVENTS
  /*! Event manager used for sample accurate MIDI and parameter scheduling */
  eventManager m_events;
#endif
  
private:
};

#endif
