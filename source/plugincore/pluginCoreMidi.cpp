/*
 *  pluginCoreMidi.cpp - pluginCore
 *
 *  Created by Nik Reiman on 19.02.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 *  This source code may NOT be redistributed without express permission of Teragon Audio.  It may be used
 *  in free or commercial software works, but unauthorized duplication or resale in whole or part is
 *  strictly prohibited.
 */

#if USE_PC_MIDI
#ifndef __pluginCore_H
#include "pluginCore.h"
#endif

void pluginCore::deleteNote(int index)
{
  if(!m_midi_notes.empty() && index <= m_midi_note_count)
  {
    std::vector<tMidiNote>::iterator iter = m_midi_notes.begin() + index;
    m_midi_notes.erase(iter);
    --m_midi_note_count;
  }
}

int pluginCore::findMidiNoteIndex(int index) const
{
  for(int i = 0; i < m_midi_note_count; ++i)
  {
    if(m_midi_notes.at(i).number == index)
    {
      return i;
    }
  }
  return -1;
}

int pluginCore::getMidiNoteCount() const
{
  return m_midi_note_count;
}

int pluginCore::getMidiNoteChannel(int index) const
{
  return m_midi_notes.at(index).channel;
}

float pluginCore::getMidiNoteFreq(int index) const
{
  return m_midi_notes.at(index).frequency;
}

float pluginCore::getMidiNoteTableFreq(int note) const
{
  return m_freq_table[note];
}

int pluginCore::getMidiNoteNumber(int index) const
{
  return m_midi_notes.at(index).number;
}

long pluginCore::getMidiNoteReserved(int index) const
{
  return m_midi_notes.at(index).reserved;
}

int pluginCore::getMidiNoteVelocity(int index) const
{
  return m_midi_notes.at(index).velocity;
}

void pluginCore::processMidi(int status, int channel, int byte1, int byte2, long frames)
{
#if 0
    m_logger->log(XML_LOGGER_TYPE_MIDI, channel, byte1, byte2, (int)frames);
#endif
  
  // Most modern hosts will attempt to schedule MIDI events with a frame offset, so in this case,
  // we add the event to the wait queue and skip processing (for now).  This feature requires the
  // PluginCore event handling module, which may be included by defining USE_PC_EVENTS
#if USE_PC_EVENTS
  if(frames > 0)
  {
    tCoreEvent *ce = (tCoreEvent*)malloc(sizeof(tCoreEvent));
    ce->action = EVT_ACTION_MIDI;
    ce->data.midi_data.status = status;
    ce->data.midi_data.channel = channel;
    ce->data.midi_data.byte1 = byte1;
    ce->data.midi_data.byte2 = byte2;
    m_events.addEvent(this, frames, ce, false);
    return;
  }
#endif
  
  int index = -1;
  switch(status)
  {
    case 0x80: // Note off
      index = findMidiNoteIndex((int)byte1);
      if(index >= 0)
      {
        noteOff(m_midi_notes.at(index).number);
        deleteNote(index);
      }
      break;
    case 0x90: // Note on
		{
      index = findMidiNoteIndex((int)byte1);
      if((int)byte2)
      {
        if(index < 0)
        {
          tMidiNote note;
          note.channel = (int)channel;
          note.number = (int)byte1;
          note.velocity = (int)byte2;
          note.frequency = m_freq_table[note.number];
          note.reserved = 0;
          m_midi_notes.push_back(note);
          ++m_midi_note_count;
          noteOn(note.number, note.velocity);
          break;
        }
        else
        {
          // Note has already been added, so just change the velocity
          m_midi_notes.at(index).velocity = (int)byte2;
        }
      }
      // Velocity of zero means to actually turn off the note
      else
      {
        if(index >= 0)
        {
          noteOff(m_midi_notes.at(index).number);
          deleteNote(index);
        }
      }
      break;
    }
    case 0xa0: // Aftertouch
      index = findMidiNoteIndex((int)byte1);
      if(index >= 0)
      {
        m_midi_notes.at(index).velocity = (int)byte2;
      }
        break;
    case 0xb0: // Control change
    {
      if((int)byte2 == 120 || (int)byte2 == 123)
      {
        // Emergency catch for all notes off
        m_midi_note_count = 0;
        m_midi_notes.clear();
        break;
      }
      
      tMidiMessage cc;
      cc.channel = channel;
      cc.byte1 = byte1;
      cc.byte2 = byte2;
      cc.reserved = 0;
      
      m_midi_ccs.push(cc);
      controlChange(cc.byte1, cc.byte2);
    }
      break;
    case 0xc0: // Program change
#if USE_PC_PRESET
      // For the moment, the channel number is ignored.  Sometimes this is used to specify
      // the program bank, and then the first byte for the corresponding program number.
      // Instead, we will treat all channels the same and simply load the preset corresponding
      // to the respective byte1 value.  No bounds checking is done here because the  value
      // gets checked in loadPreset().
      if(byte1)
      {
        loadPreset((int)byte1);
      }
#endif
      break;
    case 0xd0: // Pressure change
      // Multiply the velocity of all existing notes by a factor
      for(int i = 0; i < m_midi_note_count; ++i)
      {
        m_midi_notes.at(i).velocity = (int)((float)(m_midi_notes.at(i).velocity * byte1) / 127.0);
      }
      break;
    case 0xe0: // Pitch wheel (currently not handled)
      break;
    default:
      break;
  }
}

void pluginCore::processSysex(int length, char *data)
{
  tMidiSysex sx;
  sx.length = length;
  sx.data = new unsigned char[length];
  memcpy(sx.data, data, length * sizeof(char));
  m_midi_sysex.push(sx);
  sysex(length, data[0]);
}

void pluginCore::setMidiNoteReserved(int index, long value)
{
  m_midi_notes.at(index).reserved = value;
}

void pluginCore::setTuning(float tuning)
{
  const float step = 1.059463094359f; // 12th root of 2
  // Assume we are being passed in something close to A4, so this must be converted to C2,
  // which is MIDI note number 0
  float base = tuning * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * step * step * step;
  for(int i = 0; i < NUM_MIDI_NOTES; ++i, base *= step)
  {
    m_freq_table[i] = base;
  }
}

#endif