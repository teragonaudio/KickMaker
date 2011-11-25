/*
 *  xmlLogger.cpp
 *  PluginCore
 *
 *  Created by Nik Reiman on 02.10.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __xmlLogger_H
#include "xmlLogger.h"
#endif

#if WIN32
int gettimeofday(struct timeval *tp, struct timezone *tzp)
{
  DWORD t = GetTickCount();
  tp->tv_sec = t / 1000;
  tp->tv_usec = t % 1000;
  return 0;
}
#endif

xmlLogger::xmlLogger(const char *path, int mode) :
xmlWriter(path, mode)
{
#if USE_PC_LOGGER
  /** Algorithm: */
  /** Initialize class variables. */
  m_logging_enabled = false;
  
  /** Check to see if the file pointer could be opened given the information passed into
  * the constructor.  The variable "path" should contain an absolute system path of the logfile
  * to be opened.  If no filename was passed to the constructor, then look on the user's desktop
  * for a file named XML_LOGGER_DEFAULT_NAME.  If found, then try to re-open the logfile with
  * this path. */
  if(path == NULL)
  {
    char desktop[MAX_DIR];
    if(getDesktopDir(desktop))
    {
      strncat(desktop, XML_LOGGER_DEFAULT_NAME, MAX_DIR);
      /** If the USE_PC_LOGGER_SESSION symbol is 1, then automatically create the XML file on the desktop.
      Otherwise, look to see if the logfile target already exists on the user's desktop, and if so,
      then re-open it for logging. */
#if ! XML_LOGGER_SESSION
      FILE *fp = fopen(desktop, "r");
      if(fp != NULL)
      {
        fclose(fp);
#endif
        if(openFile(desktop, mode))
        {
          /** If the file was found on the desktop, then enable logging. */
          m_logging_enabled = true;
        }
#if ! XML_LOGGER_SESSION
      }
#endif
    }
  }
  else
  {
    /** If the file could be opened directly with the path given in the constructor, then
    * enable logging. */
    if(openFile(path, mode))
    {
      m_logging_enabled = true;
    }
  }
  
  /** Initialize our timer objects. */
  gettimeofday(&m_tv, &m_tz);
  m_start_ms = m_tv.tv_sec * 1000 + m_tv.tv_usec / 1000;

  /** If the logfile could be opened, then write the global session tag to file. */
  if(m_logging_enabled)
  {
    startSession();
  }
#endif
}

xmlLogger::~xmlLogger()
{
#if USE_PC_LOGGER
  /** Closes the global "session" tag */
  if(m_logging_enabled)
  {
    closeTag();
  }
#endif
}

long xmlLogger::getTime()
{
  gettimeofday(&m_tv, &m_tz);
  return (m_tv.tv_sec * 1000) + (m_tv.tv_usec / 1000) - m_start_ms;
}

void xmlLogger::log(const char *type)
{
#if USE_PC_LOGGER
  /** Algorithm: */
  /** Check to see if logging is enabled. */
  if(m_logging_enabled)
  {
    /** Open a new tag, write the current time to it, and close it. */
    openTag(type);
    writeTagAttr("time", getTime());
    closeTag();
  }
#endif
}

void xmlLogger::log(const char *type, const char *key, const char *value)
{
#if USE_PC_LOGGER
  /** Algorithm: */
  /** Check to see if logging is enabled. */
  if(m_logging_enabled)
  {
    /** Open a new tag, and write the key and value pair to it. */
    openTag(type);
    if(value == NULL)
    {
      char emptyquotes[3] = "\"\"";
      writeTagAttr(key, emptyquotes);
    }
    else
    {
      writeTagAttr(key, value);
    }
    /** Write the current time in ms to the tag and then close it. */
    writeTagAttr("time", getTime());
    closeTag();
  }
#endif
}

void xmlLogger::log(const char *type, const char *key, const float value)
{
#if USE_PC_LOGGER
  /** Algorithm: */
  /** Check to see if logging is enabled. */
  if(m_logging_enabled)
  {
    /** Open a new tag, and write the key and value pair to it. */
    openTag(type);
    writeTagAttr(key, value);
    /** Write the current time in ms to the tag and then close it. */
    writeTagAttr("time", getTime());
    closeTag();
  }
#endif
}

void xmlLogger::log(const char *type, const char *key, const int value)
{
#if USE_PC_LOGGER
  /** Algorithm: */
  /** Check to see if logging is enabled. */
  if(m_logging_enabled)
  {
    /** Open a new tag, and write the key and value pair to it. */
    openTag(type);
    writeTagAttr(key, value);
    /** Write the current time in ms to the tag and then close it. */
    writeTagAttr("time", getTime());
    closeTag();
  }
#endif
}

void xmlLogger::log(const char *type, const char *key, const long value)
{
#if USE_PC_LOGGER
  /** Algorithm: */
  /** Check to see if logging is enabled. */
  if(m_logging_enabled)
  {
    /** Open a new tag, and write the key and value pair to it. */
    openTag(type);
    writeTagAttr(key, value);
    /** Write the current time in ms to the tag and then close it. */
    writeTagAttr("time", getTime());
    closeTag();
  }
#endif
}

void xmlLogger::log(char *type, float f1, float f2, float f3, float f4)
{
#if USE_PC_LOGGER
  /** Algorithm: */
  /** Check to see if logging is enabled. */
  if(m_logging_enabled)
  {
    /** Open a new tag, then log each of the floating point arguments to it. */
    openTag(type);
    /** Write all three arguments to the tag. */
    writeTagAttr("arg1", f1);
    writeTagAttr("arg2", f2);
    writeTagAttr("arg3", f3);
    writeTagAttr("arg4", f4);
    /** Add the time and then close the tag. */
    writeTagAttr("time", getTime());
    closeTag();
  }
#endif
}

void xmlLogger::log(char *type, int f1, int f2, int f3, int f4)
{
#if USE_PC_LOGGER
  /** Algorithm: */
  /** Check to see if logging is enabled. */
  if(m_logging_enabled)
  {
    /** Open a new tag, then log each of the floating point arguments to it. */
    openTag(type);
    /** Write all three arguments to the tag. */
    writeTagAttr("arg1", f1);
    writeTagAttr("arg2", f2);
    writeTagAttr("arg3", f3);
    writeTagAttr("arg4", f4);
    /** Add the time and then close the tag. */
    writeTagAttr("time", getTime());
    closeTag();
  }
#endif
}

void xmlLogger::logData(const char *type, const void *data, const int length)
{
#if USE_PC_LOGGER
  /** Algorithm: */
  /** Check to see if logging is enabled. */
  if(m_logging_enabled)
  {
    /** Open a new tag and then log the data stream to it.  The tag will be automatically
    * closed afterwards. */
    openTag(type);
    writeTagAttr("time", getTime());
    writeTagData(data, length);
  }
#endif
}

void xmlLogger::startSession()
{
#if USE_PC_LOGGER
  /** Algorithm: */
  /** Open up a new tag to enclose the session. */
  openTag("session");
  
  /** Get the current system date and time and log it in the session tag. */
  struct tm *t = (struct tm*)malloc(sizeof(struct tm));
  time_t now = time(NULL);
  t = localtime(&now);
  char str[32];
  snprintf(str, 32, "%02d:%02d:%02d %02d/%02d/%04d", t->tm_hour, t->tm_min, t->tm_sec,
           t->tm_mday + 1, t->tm_mon + 1, t->tm_year + 1900);
  writeTagAttr("date", str);
#endif
}