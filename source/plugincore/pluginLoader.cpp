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
#include "pluginLoader.h"
#endif

pluginLoader::pluginLoader()
{
  m_loaded = false;
  memset(m_name, 0x0, sizeof(char) * MAX_PLUG_NAME);
  m_num_channels = 1;
}

pluginLoader::~pluginLoader()
{
}

#if MAC
const FSSpec pluginLoader::getFSSpec() const
{
  FSRef ret_ref;
  FSSpec ret;
  
  OSStatus err = FSPathMakeRef((const UInt8*)&m_path, &ret_ref, false);
  err = FSGetCatalogInfo(&ret_ref, kFSCatInfoNone, NULL, NULL, &ret, NULL);
  
  return ret;
}
#endif

const char* pluginLoader::getName() const
{
  return m_name;
}

const char* pluginLoader::getPath() const
{
  return (char *)m_path;
}

void* pluginLoader::getPluginPtr() const
{
  return NULL;
}

// Open the plugin and prepare it to receive audio/midi data
bool pluginLoader::initialize()
{
  // TODO: Actually, it might be better to return 'false' here, or better yet, make this method abstract
  return true;
}

bool pluginLoader::setChannels(int num_channels)
{
  if(num_channels > 0 && num_channels <= MAX_CHANNELS) {
    m_num_channels = num_channels;
    return true;
  }
  else {
    return false;
  }
}

void pluginLoader::setName()
{
  char *last_slash, *dot;
  if((dot = strrchr(m_path, '.')) == NULL) {
    dot = NULL;
  }
  if((last_slash = strrchr(m_path,  DEF_DIR_DELIMITER)) == NULL) {
    last_slash = NULL;
  }
  
  // We should be guaranteed a full system path here
  if(last_slash) {
    if(dot) {
      strncpy(m_name, last_slash + 1, strlen(last_slash) - strlen(dot) - 1);
    }
    else {
      strncpy(m_name, last_slash + 1, strlen(m_path) - strlen(last_slash));
    }
  }
  else {
    strncpy(m_name, m_path, MAX_PLUG_NAME);
  }
}

void pluginLoader::setName(const char *name)
{
  strncpy(m_name, name, MAX_PLUG_NAME);
}

bool pluginLoader::setParameter(int index, float value, long frames)
{
  return false;
}

bool pluginLoader::setPath(const char *fname)
{
  return false;
}

// TODO: There should be more real error checking in these methods, particularly around the m_dispatch calls...
bool pluginLoader::setProgram(int num)
{
  return false;
}

bool pluginLoader::setBlocksize(int bsize)
{
  return false;
}

bool pluginLoader::setSampleRate(float srate)
{
  return true;
}
#endif