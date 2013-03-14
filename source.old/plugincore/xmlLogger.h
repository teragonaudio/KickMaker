/*
 *  xmlLogger.h
 *  PluginCore
 *
 *  Created by Nik Reiman on 02.10.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __xmlLogger_H
#define __xmlLogger_H

#include <time.h>
#if WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#endif

#ifndef __xmlWriter_H
#include "xmlWriter.h"
#endif

#ifndef __productDir_H
#include "productDir.h"
#endif

#ifndef XML_LOGGER_SESSION
/*! \brief Create a logfile all the time on the user's desktop.  If this symbol is defined to be 0,
then this class looks to see if such a file exists first, and then re-opens it */
#define XML_LOGGER_SESSION 1
#endif

#ifndef XML_LOGGER_DEFAULT_NAME
#define XML_LOGGER_DEFAULT_NAME "logfile.xml"
#endif

#define XML_LOGGER_TYPE_NONE "none"
#define XML_LOGGER_TYPE_MIDI "midi"
#define XML_LOGGER_TYPE_GET_PARAMETER "getparameter"
#define XML_LOGGER_TYPE_SET_PARAMETER "setparameter"
#define XML_LOGGER_TYPE_GET_STATE "getstate"
#define XML_LOGGER_TYPE_SET_STATE "setstate"
#define XML_LOGGER_TYPE_STATUS "status"
#define XML_LOGGER_TYPE_STRING "string"
#define XML_LOGGER_TYPE_PROCESS "process"
#define XML_LOGGER_TYPE_RESET "reset"
#define XML_LOGGER_TYPE_LOAD_PRESET "loadpreset"
#define XML_LOGGER_TYPE_SAVE_PRESET "savepreset"
#define XML_LOGGER_TYPE_DELETE_PRESET "deletepreset"

#if WINDOWS
struct timezone
{
  int tz_minuteswest;
  int tz_dsttime;
};
#endif

#if WINDOWS
/*! \brief Windows compatibility function.  Behaves exactly like the unix gettimeofday(). */
int gettimeofday(struct timeval *tp, struct timezone *tzp);
#endif

class xmlLogger : public xmlWriter
{
public:
  /*! \brief Create a new logging object
  * \param path A string containing the absolute path of the logfile to write to.
  * If this parameter is not given, then the constructor will attempt to open the file
  * named XML_LOGGER_DEFAULT_NAME located on the user's desktop.  If neither one
  * of these conditions are met, then logging will be disabled.
  * \param mode The open mode that should be used for the logfile.  May be either
  * XML_WRITER_MODE_WRITE or XML_WRITER_MODE_APPEND.
  */
  xmlLogger(const char *path = NULL, int mode = XML_WRITER_MODE_APPEND);
  virtual ~xmlLogger();
  
  /*! \brief Get the current time in milliseconds. */ 
  long getTime();
  
  /*! \brief Log a single tag without any additional arguments
  * \param type The tag type
  */
  virtual void log(const char *type);
  
  /*! \brief Log an entry in the file
  * \param type The type of tag to write.  Should be one of the XML_LOGGER_TYPE definitions,
  * but other tag names can be used if desired
  * \param key The key name for a key/value pair
  * \param value The value string
  */
  virtual void log(const char *type, const char *key, const char *value = NULL);
  virtual void log(const char *type, const char *key, const float value);
  virtual void log(const char *type, const char *key, const int value);
  virtual void log(const char *type, const char *key, const long value);
  
  /*! \brief Log up to four floating point numbers
  * \param type The type of tag to write
  * \param f1 First argument (required)
  * \param f2 Second argument (optional)
  * \param f3 Third argument (optional)
  * \param f4 Fourth argument (optional)
  */
    /*
  virtual void log(const char *type, float f1, float f2 = 0.0, float f3 = 0.0, float f4 = 0.0);
  virtual void log(char *type, int f1, int f2 = 0, int f3 = 0, int f4 = 0);
  */
  /*! \brief Log a chunk of data
  * \param type The type of tag to write
  * \param data A pointer to the data block
  * \param length The size (in bytes) of the block
  */
  virtual void logData(const char *type, const void *data, const int length);
  
protected:
  /*! \brief Initialize a logging session */
  virtual void startSession();
  
  /*! Used to cache system time info */
  struct timeval m_tv;
  /*! Used to cache system time info */
  struct timezone m_tz;
  /*! True or false depending on whether a logfile could be opened */
  bool m_logging_enabled;
  /*! Number of milliseconds since logging started */
  unsigned long m_start_ms;
  
private:
};

#endif