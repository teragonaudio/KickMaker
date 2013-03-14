/*
 *  pluginCorePreset.cpp - pluginCore
 *
 *  Created by Nik Reiman on 19.02.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 *  This source code may NOT be redistributed without express permission of Teragon Audio.  It may be used
 *  in free or commercial software works, but unauthorized duplication or resale in whole or part is
 *  strictly prohibited.
 */

#if USE_PC_PRESET
#ifndef __pluginCore_H
#include "pluginCore.h"
#endif

void pluginCore::addPreset(tPreset *preset)
{
  m_presets.push_back(*preset);
  ++m_num_presets;
}

void pluginCore::deletePreset(const char *name, const char *bank)
{
  return deletePreset(findPreset(name));
}

void pluginCore::deletePreset(int index)
{
  // Prevent deleting invalid indexes
  if(index < 0 || index >= m_num_presets)
    return;

  m_logger->log(XML_LOGGER_TYPE_DELETE_PRESET, "index", 0);
  
  // If the preset is part of a bank, just remove it from the list
  if(m_presets.at(index).bank[0] == '\0')
  {
    unlink(m_presets.at(index).full_path);
  }
  
  std::vector<tPreset>::iterator iter = m_presets.begin() + index;
  m_presets.erase(iter);
  --m_num_presets;
}

int pluginCore::findPreset(const char *name, const char *bank) const
{
  for(int i = 0; i < m_num_presets; ++i)
  {
    if(!strcmp(name, m_presets.at(i).name))
    {
      if(bank)
      {
        if(!strcmp(bank, m_presets.at(i).bank))
        {
          return i;
        }
      }
      else
      {
        return i;
      }
    }
  }
  return -1;
}

int pluginCore::getCurrentPresetIndex() const
{
  return m_cur_preset;
}

void pluginCore::getCurrentPresetBank(char *text) const
{
  if(m_cur_preset < 0 || m_num_presets == 0)
  {
    text[0] = '\0';
  }
  else
  {
    getPresetBank(m_cur_preset, text);
  }
}

void pluginCore::getCurrentPresetName(char *text) const
{
  if(m_cur_preset < 0 || m_num_presets == 0)
  {
    text[0] = '\0';
  }
  else
  {
    getPresetName(m_cur_preset, text);
  }
}

int pluginCore::getNumPresets() const
{
  return m_num_presets;
}

void pluginCore::getPresetBank(int index, char *text) const
{
  if(index >= 0 && index < m_num_presets && m_presets.at(index).bank)
  {
    strncpy(text, m_presets.at(index).bank, MAX_NAME);
  }
  else
  {
    text[0] = '\0';
  }
}

void pluginCore::getPresetName(int index, char *text) const
{
  if(index < m_num_presets && index >= 0)
  {
    strncpy(text, m_presets.at(index).name, MAX_NAME);
  }
  else
  {
    text[0] = '\0';
  }
}

void pluginCore::loadPreset(const char *name, const char *bank)
{
  return loadPreset(findPreset(name, bank));
}

void pluginCore::loadPreset(int index)
{
  if(index >= m_num_presets || index < 0)
    return;
  
  m_logger->log(XML_LOGGER_TYPE_LOAD_PRESET, "index", index);
  for(int i = 0; i < m_num_params && i < m_presets.at(index).num_params; ++i)
  {
    float preval = m_presets.at(index).data[i].value;
    if(preval > m_params[i].maxval)
    {
      preval = m_params[i].maxval;
    }
    else if(preval < m_params[i].minval)
    {
      preval = m_params[i].minval;
    }
    
    setParameter(i, preval);
  }
  
  m_cur_preset = index;
}

void pluginCore::nextPreset()
{
  if(m_num_presets > 0)
  {
    if(m_cur_preset + 1 >= m_num_presets)
    {
      loadPreset(0);
    }
    else
    {
      loadPreset(m_cur_preset + 1);
    }
  }
}

void XMLCALL pluginCore::presetDataHandler(void *userData, const XML_Char *string, int len)
{
  // This should contain chunked data for a parameter
}

void XMLCALL pluginCore::presetElementStartHandler(void *userData, const char *name, const char **atts)
{
  int i = 0;
  static char bank[MAX_NAME];
  std::vector<tPreset> *p = ((std::vector<tPreset>*)userData);
  int cur = p->size() - 1;
  
  if(!strcmp(name, DEF_PARAMETER_TAG))
  {
    if(cur < 0)
      return;
    
    char name[MAX_NAME];
    float minval, maxval, value = 0.0f;
    int index = 0;
    
    while(atts[i] != NULL)
    {
      if(!strcmp(atts[i], "name")) {
        strncpy(name, atts[++i], MAX_NAME);
      }
      else if(!strcmp(atts[i], "maxval")) {
        maxval = (float)atof(atts[++i]);
      }
      else if(!strcmp(atts[i], "minval")) {
        minval = (float)atof(atts[++i]);
      }
      else if(!strcmp(atts[i], "index")) {
        index = atoi(atts[++i]);
      }
      else if(!strcmp(atts[i], "value")) {
        value = (float)atof(atts[++i]);
      }
      ++i;
    }
    
    strncpy(p->at(cur).data[index].name, name, MAX_NAME);
    p->at(cur).data[index].maxval = maxval;
    p->at(cur).data[index].minval = minval;
    p->at(cur).data[index].value = value;
    p->at(cur).data[index].index = index;
  }
  else if(!strcmp(name, DEF_PRESET_TAG))
  {
    tPreset preset;
    memset(&preset, 0x0, sizeof(tPreset));
    strncpy(preset.bank, bank, MAX_NAME);
    
    while(atts[i] != NULL)
    {
      if(!strcmp(atts[i], "name")) {
        strncpy(preset.name, atts[++i], MAX_NAME);
      }
      else if(!strcmp(atts[i], "author")) {
      }
      else if(!strcmp(atts[i], "product")) {
      }
      else if(!strcmp(atts[i], "version")) {
      }
      else if(!strcmp(atts[i], "parameters")) {
        preset.num_params = atoi(atts[++i]);
        if(!(preset.data)) {
          preset.data = new tParam[preset.num_params];
        }
        
      }
      ++i;
    }
    
    strncpy(preset.bank, bank, MAX_NAME);
    p->push_back(preset);
  }
  else if(!strcmp(name, DEF_BANK_TAG))
  {
    memset(bank, 0x0, sizeof(char) * MAX_NAME);
    
    while(atts[i] != NULL)
    {
      if(!strcmp(atts[i], "name")) {
        strncpy(bank, atts[++i], MAX_NAME);
      }
      else if(!strcmp(atts[i], "author")) {
        ++i;
      }
      ++i;
    }
  }
  else {
  }
}

void XMLCALL pluginCore::presetElementEndHandler(void *userData, const char *name)
{
}

void pluginCore::prevPreset()
{
  if(m_num_presets > 0)
  {
    if(m_cur_preset - 1 < 0)
    {
      loadPreset(m_num_presets - 1);
    }
    else
    {
      loadPreset(m_cur_preset - 1);
    }
  }
}

void pluginCore::readPreset(const char *path)
{
  // Ignore everything without the default extension
  char *ext = strrchr((char*)path, '.');
  if(ext == NULL)
    return;
  else if(strcmp(ext, DEF_PRESET_EXTENSION))
    return;

  FILE *fp = fopen(path, "r");
  if(fp == NULL)
    return;
  
  int done = 0;
  char buf[1024];
  int prev_index = m_presets.size() - 1;
  if(prev_index < 0) {
    prev_index = 0;
  }
  
  XML_Parser parser = XML_ParserCreate(NULL);
  XML_SetCharacterDataHandler(parser, presetDataHandler);
  XML_SetUserData(parser, &m_presets);
  XML_SetElementHandler(parser, presetElementStartHandler, presetElementEndHandler);
  
  do
  {
    size_t len = fread(buf, 1, sizeof(buf), fp);
    done = len < sizeof(buf);
    if(XML_Parse(parser, buf, len, done) == XML_STATUS_ERROR) {
      fprintf(stderr,
              "%s at line %" XML_FMT_INT_MOD "u\n",
              XML_ErrorString(XML_GetErrorCode(parser)),
              XML_GetCurrentLineNumber(parser));
      break;
    }
  } while(!done);
  
  XML_ParserFree(parser);
  fclose(fp);
  m_num_presets = m_presets.size();
  for(; prev_index < m_num_presets; ++prev_index)
  {
    strncpy(m_presets.at(prev_index).full_path, path, MAX_PATH_SIZE);
  }
}

bool pluginCore::savePreset(const char *product, char *name, const char *bank) {
  if(!name || strlen(name) == 0)
    return false;
  
  m_logger->log(XML_LOGGER_TYPE_SAVE_PRESET, "name", name);
  // First check to see if this is a new preset or re-writing an old preset
  int num = findPreset(name);
  bool newpreset = true;
  if(num >= 0)
  {
    newpreset = false;
  }
  
  char path[MAX_DIR];
  if(!getProductDir(product, (char*)&path))
    return false;
  
  stripSpecialChars(name);
  strncat(path, name, MAX_DIR);
  strncat(path, DEF_PRESET_EXTENSION, MAX_DIR);
  FILE *fp = fopen(path, "w");
  if(fp == NULL) 
    return false;
  
  xmlWriter *xml_fp = new xmlWriter(path, XML_WRITER_MODE_WRITE);
  // \todo Expand author and other optional tags
  xml_fp->openTag("preset");
  xml_fp->writeTagAttr("name", name);
  xml_fp->writeTagAttr("parameters", m_num_params);
  
  // \todo Write a preset within an existing bank's file
  char prm_name[MAX_NAME];
  for(int i = 0; i < m_num_params; ++i)
  {
    memset(prm_name, 0x0, sizeof(char) * MAX_NAME);
    getParameter(REQ_NAME, i, prm_name);
    xml_fp->openTag("parameter");
    xml_fp->writeTagAttr("name", prm_name);
    xml_fp->writeTagAttr("minval", getParameter(REQ_VALUE_MIN, i));
    xml_fp->writeTagAttr("maxval", getParameter(REQ_VALUE_MAX, i));
    xml_fp->writeTagAttr("value", PARAM(i));
    xml_fp->closeTag();
  }
  
  xml_fp->closeTag();
  delete xml_fp;
  
  fclose(fp);
  
  if(newpreset)
  {
    readPreset(path);
    return true;
  }
  else
  {
    for(int i = 0; i < m_num_params; ++i)
    {
      m_presets[num].data[i].value = m_params[i].value;
    }
    return false;
  }
}

bool pluginCore::setPresetBank(const char *bank)
{
  return true;
}

int pluginCore::slurpDirectory(char *path, bool recursive)
{
  char fullpath[MAX_DIR];
  int count = 0;
  
#if MAC
  DIR *dp = opendir(path);
  
  if(dp == NULL)
    return 0;
  
  dirent *dir_st;
  while((dir_st = readdir(dp)))
  {
    if(dir_st->d_name[0] == '.')
      continue;
    else if(recursive && dir_st->d_type == DT_DIR)
    {
      char child[MAX_DIR];
      snprintf(child, MAX_DIR, "%s%s%c", path, dir_st->d_name, DEF_DIR_DELIMITER);
      count += slurpDirectory(child, recursive);
    }
    else if(strstr(dir_st->d_name, DEF_PRESET_EXTENSION))
    {
      sprintf(fullpath, "%s%s", path, dir_st->d_name);
      readPreset(fullpath);
      ++count;
    }
  }
  
  closedir(dp);
#elif WIN32
  HANDLE hlist;
  WIN32_FIND_DATA filedata;
  
  char searchpath[MAX_DIR];
  _snprintf(searchpath, MAX_DIR, "%s*", path);
  hlist = FindFirstFile(searchpath, &filedata);
  if(hlist == INVALID_HANDLE_VALUE)
  {
    FindClose(hlist);
    return 0;
  }
  else
  {
    bool done = false;
    while(!done)
    {
      if(filedata.cFileName[0] != '.')
      {
        if(!(filedata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
          sprintf(fullpath, "%s%s", path, filedata.cFileName);
          readPreset(fullpath);
          ++count;
        }
        else
        {
          if(recursive)
          {
            char child[MAX_DIR];
            _snprintf(child, MAX_DIR, "%s%s%c", path, filedata.cFileName,
                      DEF_DIR_DELIMITER);
            count += slurpDirectory(child, recursive);
          }
        }
      }
      
      if(!FindNextFile(hlist, &filedata))
      {
        if(GetLastError() == ERROR_NO_MORE_FILES)
        {
          done = true;
        }
      }
    }
    
    FindClose(hlist);
  }
#endif
  
  return count;
}

void pluginCore::stripSpecialChars(char *string) const
{
  for(unsigned int i = 0; i < strlen(string); ++i)
  {
    if(!((string[i] >= '0' && string[i] <= '9') ||
         (string[i] >= 'A' && string[i] <= 'Z') ||
         (string[i] >= 'a' && string[i] <= 'z')))
    {
      string[i] = DEF_REPLACEMENT_DELIMITER;
    }
  }
}

#endif