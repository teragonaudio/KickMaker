/*
 *  pluginCore.cpp - pluginCore
 *
 *  Created by Nik Reiman on 27.12.05.
 *  Copyright 2005 Teragon Audio. All rights reserved.
 *
 *  This source code may NOT be redistributed without express permission of Teragon Audio.  It may be used
 *  in free or commercial software works, but unauthorized duplication or resale in whole or part is
 *  strictly prohibited.
 */

#ifndef __pluginCore_H
#include "pluginCore.h"
#endif

/*! Used to provide string labels for AU parameter types.  See also pluginCore::DEF_PARAM_TYPE. */
static tLabel labels[] =
{
  { kAudioUnitParameterUnit_AbsoluteCents, "Cents" },
  { kAudioUnitParameterUnit_Beats, "Beats" },
  { kAudioUnitParameterUnit_Boolean, "T/F" },
  { kAudioUnitParameterUnit_BPM, "BPM" },
  { kAudioUnitParameterUnit_Cents, "Ct" },
  { kAudioUnitParameterUnit_CustomUnit, " " },
  { kAudioUnitParameterUnit_Decibels, "dB" },
  { kAudioUnitParameterUnit_Degrees, "Deg" },
  { kAudioUnitParameterUnit_EqualPowerCrossfade, "X-fade" },
  { kAudioUnitParameterUnit_Generic, "" },
  { kAudioUnitParameterUnit_Hertz, "Hz" },
  { kAudioUnitParameterUnit_Indexed, "Note" },
  { kAudioUnitParameterUnit_LinearGain, "" },
  { kAudioUnitParameterUnit_MIDIController, "CC" },
  { kAudioUnitParameterUnit_MIDINoteNumber, "Note" },
  { kAudioUnitParameterUnit_Meters, "Meters" },
  { kAudioUnitParameterUnit_Milliseconds, "ms" },
  { kAudioUnitParameterUnit_MixerFaderCurve1, "" },
  { kAudioUnitParameterUnit_Octaves, "Octave" },
  { kAudioUnitParameterUnit_Pan, "Pan" },
  { kAudioUnitParameterUnit_Percent, "%" },
  { kAudioUnitParameterUnit_Phase, "Phase" },
  { kAudioUnitParameterUnit_Rate, "Rate" },
  { kAudioUnitParameterUnit_Ratio, "Ratio" },
  { kAudioUnitParameterUnit_RelativeSemiTones, "Semitones" },
  { kAudioUnitParameterUnit_SampleFrames, "Frames" },
  { kAudioUnitParameterUnit_Seconds, "Sec" },
  { kAudioUnitParameterUnit_Hertz, "Hz" },
  { kAudioUnitParameterUnit_Generic, "String" },
  { kAudioUnitParameterUnit_Generic, "Chunk" }
};

// Implementation //////////////////////////////////////////////////////////////////////

pluginCore::pluginCore(int num_params, long version, const char *name, char *logfile, int logmode)
#if USE_PC_EVENTS
: eventListener()
#endif
{
  m_num_params = num_params;
  m_params = new tParam[num_params];
  setVersion(version);
  m_logger = new xmlLogger(logfile, logmode);
  m_logger->log(XML_LOGGER_TYPE_STATUS, "starting");
  
#if USE_PC_PRESET
  m_num_presets = 0;
  m_cur_preset = -1;
#endif
  
#if USE_PC_MIDI
  m_midi_note_count = 0;
  setTuning(DEF_TUNING);
#endif
  
  if(name == NULL)
  {
    strncpy(m_name, "Unknown", MAX_NAME);
  }
  else
  {
    strncpy(m_name, name, MAX_NAME);
  }
  
  
  m_logger->log(XML_LOGGER_TYPE_STATUS, "pluginloaded", name);
}

pluginCore::~pluginCore()
{
  m_logger->log(XML_LOGGER_TYPE_STATUS, "pluginunloading", m_name);

#if USE_PC_PRESET
  for(int i = 0; i < m_num_presets; ++i)
  {
    delete m_presets.at(i).data;
  }
#endif
  
  for(int i = 0; i < m_num_params; ++i)
  {
    if(m_params[i].chunk_size > 0)
    {
      free(m_params[i].chunk);
    }
  }
  delete [] m_params;

  m_logger->log(XML_LOGGER_TYPE_STATUS, "closing");
  delete m_logger;
}

void pluginCore::addParameter(int index, const char *display, int type,
                              float minval, float maxval, float initval,
                              bool lock, int size)
{
  if(index >= m_num_params || index < 0)
    return;
  
  strncpy(m_params[index].name, display, MAX_NAME);
  m_params[index].type = type;
  m_params[index].lock = lock;
  m_params[index].minval = minval;
  if(type == TYP_HZ_LOG && minval == 0.0)
  {
    minval = DEF_DC_OFFSET;
  }
  m_params[index].maxval = maxval;
  m_params[index].value = initval;
  m_params[index].defval = initval;
  m_params[index].chunk_size = 0;
  m_params[index].chunk = NULL;
}

float pluginCore::getParameter(int request, int index, void *sdata) const
{
  if(index >= m_num_params || index < 0)
  {
    return -1.0;
  }

  m_logger->log(XML_LOGGER_TYPE_GET_PARAMETER, "parameter", index);
  switch(request)
  {
    case REQ_VALUE:
#ifdef USE_PC_VST
      return getParameterScaled(index);
#endif
    case REQ_VALUE_RAW:
      return m_params[index].value;
    case REQ_NAME:
      if(sdata)
      {
#ifndef DEBUG
        if(m_params[index].lock)
        {
          strcpy((char*)sdata, DEF_HIDDEN_PARAM_NAME);
          return 0.0;
        }
#endif
        strcpy((char*)sdata, m_params[index].name);
        if(m_params[index].lock)
        {
          strcat((char*)sdata, "*");
        }
        return 0.0;
      }
      return -1.0;
    case REQ_DISPLAY:
      if(sdata)
      {
        switch(m_params[index].type)
        {
          case TYP_BOOL:
            if(m_params[index].value)
            {
              strcpy((char*)sdata, "On");
            }
            else
            {
              strcpy((char*)sdata, "Off");
            }
            break;
          case TYP_CUSTOM:
          case TYP_SAMPLEFRAMES:
            sprintf((char*)sdata, "%d", (int)m_params[index].value);
            break;
          case TYP_PERCENT:
            sprintf((char*)sdata, "%2.1f", m_params[index].value);
            break;
          default:
            sprintf((char*)sdata, "%.02f", m_params[index].value);
            break;
        }
        return 0.0;
      }
    case REQ_LABEL:
#if USE_PC_AU
      return labels[m_params[index].type].aucode;
#elif USE_PC_VST
      if(sdata)
      {
        strcpy((char*)sdata, labels[m_params[index].type].label);
        return 0.0;
      }
        return -1.0;
#endif
    case REQ_LABEL_STR:
      if(sdata)
      {
        strcpy((char*)sdata, labels[m_params[index].type].label);
        return 0.0;
      }
      return -1.0;
      break;
    case REQ_VALUE_MIN:
      return m_params[index].minval;
    case REQ_VALUE_MAX:
      return m_params[index].maxval;
    case REQ_VALUE_DEF:
      return m_params[index].defval;
    case REQ_CHUNK_SIZE:
      return (float)m_params[index].chunk_size;
    case REQ_CHUNK:
      if(m_params[index].chunk_size <= 0)
        return -1.0;
      memcpy(sdata, m_params[index].chunk, m_params[index].chunk_size);
      return 0.0; 
    default:
      return -1.0;
  }
}

float pluginCore::getParameterScaled(int index) const
{
  if(index >= m_num_params || index < 0)
  {
    return -1.0;
  }
  else if(m_params[index].type == TYP_HZ_LOG)
  {
    return (log(m_params[index].value) - log(m_params[index].minval)) /
    (log(m_params[index].maxval) - log(m_params[index].minval));
  }
  else
  {
    return (m_params[index].value - m_params[index].minval) /
    (m_params[index].maxval - m_params[index].minval);
  }
}

unsigned char* pluginCore::getState(int &bytes)
{
  /** Algorithm: */
  std::vector<tIFFChunk> elements;
  tIFFChunk iff;
  unsigned char *cbuf = 0;
  
  m_logger->log(XML_LOGGER_TYPE_GET_STATE);
  
#if USE_PC_PRESET
  /** Prepare information about the current preset and bank names. */
  iff.type = STR2FOURCC(DEF_PRESET_BANK_TYPE);
  iff.length = sizeof(char) * MAX_NAME;
  iff.value = 0.0;
  elements.push_back(iff);
  
  iff.type = STR2FOURCC(DEF_PRESET_NAME_TYPE);
  iff.length = sizeof(float);
  iff.value = (float)getCurrentPresetIndex();
  elements.push_back(iff);
#endif
  
  /** Get size info for all parameters, including associated data chunks. */
  for(int i = 0; i < m_num_params; ++i) {
    memset(&iff, 0x0, sizeof(tIFFChunk));
    iff.type = STR2FOURCC(DEF_PARAM_TYPE);
    iff.length = m_params[i].chunk_size + sizeof(float);
    iff.value = PARAM(i);
    elements.push_back(iff);
  }
  
  /** Calculate total size for all elements (including header sizes). */
  int num_bytes = 0;
  for(unsigned int i = 0; i < elements.size(); ++i) {
    num_bytes += elements.at(i).length + sizeof(int) + sizeof(int);
  }
  
  unsigned char *userData = (unsigned char *)malloc(num_bytes + sizeof(int) + sizeof(int));
  memset(userData, 0x0, num_bytes + sizeof(int) + sizeof(int));
  
  /** Write the required FORM header for IFF data. */
  iff.type = 'FORM';
  iff.length = num_bytes;
  memcpy(userData + bytes, &iff.type, sizeof(int));
  bytes += sizeof(int);
  memcpy(userData + bytes, &iff.length, sizeof(int));
  bytes += sizeof(int);
  
  int start = 0;
  
#if USE_PC_PRESET
  /** Retrieve and then write the preset bank name in its own chunk. */
  memcpy(userData + bytes, &(elements.at(0).type), sizeof(int));
  bytes += sizeof(int);
  memcpy(userData + bytes, &(elements.at(0).length), sizeof(int));
  bytes += sizeof(int);
  ++start;
  
  cbuf = new unsigned char[MAX_NAME];
  getCurrentPresetBank((char*)cbuf);
  memcpy(userData + bytes, cbuf, sizeof(char) * MAX_NAME);
  bytes += sizeof(char) * MAX_NAME;
  delete [] cbuf;
  
  /** Write the current preset number. */
  memcpy(userData + bytes, &(elements.at(1).type), sizeof(int));
  bytes += sizeof(int);
  memcpy(userData + bytes, &(elements.at(1).length), sizeof(int));
  bytes += sizeof(int);
  memcpy(userData + bytes, &(elements.at(1).value), sizeof(float));
  bytes += sizeof(float);
  ++start;
#endif
  
  /** Write values and chunks for all parameters. */
  for(unsigned int i = start; i < elements.size(); ++i)
  {
    memcpy(userData + bytes, &(elements.at(i).type), sizeof(int));
    bytes += sizeof(int);
    memcpy(userData + bytes, &(elements.at(i).length), sizeof(int));
    bytes += sizeof(int);
    memcpy(userData + bytes, &(elements.at(i).value), sizeof(float));
    bytes += sizeof(float);
    if(elements.at(i).length > sizeof(float))
    {
      if(cbuf)
      {
        delete [] cbuf;
      }
      cbuf = new unsigned char[elements.at(i).length];
      memcpy(userData + bytes, &cbuf, elements.at(i).length);
      bytes += elements.at(i).length;
      delete [] cbuf;
    }
  }

  return userData;
}

long pluginCore::getVersion() const
{
  m_logger->log(XML_LOGGER_TYPE_STATUS, "getversion", (int)m_version);
  return m_version;
}

#if USE_PC_EVENTS
void pluginCore::handleEvent(void *data)
{
  if(data)
  {
    tCoreEvent *d = (tCoreEvent*)data;
    if(d->action == EVT_ACTION_PARAM)
    {
      setParameter(d->data.param_data.index, d->data.param_data.value, true);
      free(d->data.param_data.chunk);
    }
#if USE_PC_MIDI
    else if(d->action == EVT_ACTION_MIDI)
    {
      processMidi(d->data.midi_data.status, d->data.midi_data.channel,
                  d->data.midi_data.byte1, d->data.midi_data.byte2, 0);
    }
#endif
    else {
    }
  }
  else {
  }
}
#endif

void pluginCore::lockParameter(int index, bool lock)
{
  if(index > m_num_params)
    return;
  
  m_params[index].lock = lock;
}

inline void pluginCore::process(float **inputs, float **outputs, long frames)
{
  m_logger->log(XML_LOGGER_TYPE_PROCESS, "frames", frames);
#if USE_PC_EVENTS
  m_events.update(frames);
#endif
}

void pluginCore::reset()
{
  m_logger->log(XML_LOGGER_TYPE_RESET);
}

bool pluginCore::setParameter(int index, float value, bool override, long frames)
{
  if(index >= m_num_params || index < 0 || (m_params[index].lock && !override))
    return false;
  
#if USE_PC_EVENTS
  if(frames > 0)
  {
    tCoreEvent *ce = (tCoreEvent*)malloc(sizeof(tCoreEvent));
    ce->action = EVT_ACTION_PARAM;
    ce->data.param_data.index = index;
    ce->data.param_data.value = value;
    m_events.addEvent(this, frames, ce, false);
    return false;
  }
#endif
  
#if 0
  m_logger->log(XML_LOGGER_TYPE_SET_PARAMETER, (float)index, (float)value);
#endif
  
#if USE_PC_AU
  if(m_params[index].type == TYP_CUSTOM) {
    value = (int)value;
  }
  m_params[index].value = value;
#endif
#ifdef USE_PC_VST
  // Raw value has been passed in
  if(value >= 1.0 && m_params[index].maxval > 1.0) {
    m_params[index].value = value;
  }
  else if(value < 1.0 && m_params[index].maxval < 1.0) {
    m_params[index].value = value;
  }
  // Manually normalize the parameter value for everything else
  else {
    if(m_params[index].type == TYP_BOOL) {
      if(value > 0.5) {
        m_params[index].value = 1.0;
      }
      else {
        m_params[index].value = 0.0;
      }
    }
    else {
      return setParameterScaled(index, value);
    }
  }
#endif
  
  return true;
}

bool pluginCore::setParameter(int index, void *chunk, int chunk_size, bool override, long frames)
{
  if(index >= m_num_params || index < 0 || chunk_size <= 0 && (m_params[index].lock && !override))
    return false;
  
#if USE_PC_EVENTS
  if(frames > 0)
  {
    tCoreEvent *ce = (tCoreEvent*)malloc(sizeof(tCoreEvent));
    ce->action = EVT_ACTION_PARAM;
    ce->data.param_data.index = index;
    ce->data.param_data.chunk_size = chunk_size;
    ce->data.param_data.chunk = malloc(chunk_size);
    memcpy(ce->data.param_data.chunk, chunk, chunk_size);
    m_events.addEvent(this, frames, ce, false);
    return false;
  }
#endif
  
  m_params[index].chunk_size = chunk_size;
  if(m_params[index].chunk) {
    free(m_params[index].chunk);
  }
  m_params[index].chunk = malloc(chunk_size);
  memcpy(m_params[index].chunk, chunk, chunk_size);
  return true;
}

bool pluginCore::setParameterScaled(int index, float value, bool lock) {
  if(index >= m_num_params || index < 0) {
    return false;
  }
  
  if(lock || !m_params[index].lock) {
    if(m_params[index].type == TYP_HZ_LOG) {
      // Convert between decibels and linear value
      m_params[index].value = exp(value * (log(m_params[index].maxval) - log(m_params[index].minval)) +
                                  log(m_params[index].minval));
    }
    else if(m_params[index].type == TYP_BOOL)
    {
      if(value > 0.5)
      {
        m_params[index].value = 1.0;
      }
      else
      {
        m_params[index].value = 0.0;
      }
    }
    else {
      m_params[index].value = value * (m_params[index].maxval - m_params[index].minval) + m_params[index].minval;
    }
  }
  
  return true;
}

bool pluginCore::setState(unsigned char *userData, unsigned int length) {
  /** Algorithm: */
  /** Return immediately if there is no data at all, or no data within the "FORM" section. */
  if(!length || length < (sizeof(int) + sizeof(int)))
    return false;
  
  m_logger->log(XML_LOGGER_TYPE_SET_STATE);
  
  tIFFChunk iff;
  /** First read the IFF header to see if this is really our data. */
  memcpy(&iff.type, userData, sizeof(int));
  memcpy(&iff.length, userData + sizeof(int), sizeof(int));
  
  unsigned int bytes = 0, param_num = 0;
  /** Read in the FORM chunk (required in all IFF document types), and get the total size in bytes. */
  if(iff.type == STR2FOURCC("FORM"))
  {
    while(bytes < length)
    {
      memset(&iff, 0x0, sizeof(tIFFChunk));
      memcpy(&iff.type, userData + bytes, sizeof(int));
      bytes += sizeof(int);
      memcpy(&iff.length, userData + bytes, sizeof(int));
      bytes += sizeof(int);
      /** If a preset bank chunk is found, then extract the bank name and set the preset bank with it. */
      if(iff.type == STR2FOURCC(DEF_PRESET_BANK_TYPE))
      {
        char bname[MAX_NAME];
        memset(bname, 0x0, sizeof(char) * MAX_NAME);
        memcpy(&bname, userData + bytes, iff.length);
        bytes += iff.length;
#if USE_PC_PRESET
        setPresetBank(bname);
#endif
      }
      /** If a preset name is found, then extract the name and set the current preset to this name. */
      else if(iff.type == STR2FOURCC(DEF_PRESET_NAME_TYPE))
      {
        float data;
        memcpy(&data, userData + bytes, sizeof(float));
        bytes += sizeof(float);
#if USE_PC_PRESET
        loadPreset((int)data);
#endif
      }
      /** For each parameter found, initialize a new tIFFChunk to hold the parameter, extract parameter
        * data, and then set the parameter information in the plugin. */
      else if(iff.type == STR2FOURCC(DEF_PARAM_TYPE))
      {
        memcpy(&iff.value, userData + bytes, sizeof(float));
        bytes += sizeof(float);
        setParameter(param_num, iff.value);
        if(iff.length > sizeof(float))
        {
          unsigned char *cbuf = (unsigned char*)malloc(iff.length - sizeof(float));
          memcpy(cbuf, userData + bytes, iff.length - sizeof(float));
          bytes += iff.length - sizeof(float);
          delete [] cbuf;
        }
        ++param_num;
      }
    }
  }
  else
  {
    return false;
  }
  
  return true;
}

void pluginCore::setVersion(long version)
{
  m_version = version;
}
