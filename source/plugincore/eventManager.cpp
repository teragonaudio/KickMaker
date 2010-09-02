/*
 *  eventManager.cpp - pluginCore
 *
 *  Created by Nik Reiman on 28.02.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 *  This source code may NOT be redistributed without express permission of Teragon Audio.  It may be used
 *  in free or commercial software works, but unauthorized duplication or resale in whole or part is
 *  strictly prohibited.
 */

#if USE_PC_EVENTS

#ifndef __eventManager_H
#include "eventManager.h"
#endif

void eventManager::addEvent(eventListener *el, int bars, int beats, int sixteenths, void *data, bool update) {
  if(m_bpm && m_quarter_factor && m_sample_rate) {
    addEvent(el, (long)((m_quarter_factor *
                         ((((double)bars - 1.0) * m_upper) +                 
                          ((double)beats - 1.0) +
                          ((((double)sixteenths - 1.0) * m_lower) / 16.0)) *
                         60.0 / m_bpm) * m_sample_rate), data, update);
  }
}

void eventManager::addEvent(eventListener *el, long ticks, void *data, bool update) {
  if(update) {
    for(unsigned int i = 0; i < m_events.size(); ++i) {
      if(m_events.at(i)->listener == el) {
        m_events.at(i)->ticks = ticks;
        m_events.at(i)->data = data;
        return;
      }
    }
  }
  
  tEvent *event = new tEvent;
  event->listener = el;
  event->ticks = ticks;
  event->data = data;
  
  m_events.push_back(event);
}

void eventManager::setBPM(double bpm) {
  if(bpm > 0) {
    m_bpm = bpm;
  }
}

void eventManager::setSampleRate(float srate) {
  m_sample_rate = srate;
}

void eventManager::setTimeSignature(double upper, double lower) {
  if(upper >= 1.0 && lower >= 1.0) {
    m_upper = upper;
    m_lower = lower;
    // Since the conversion between beats/bars/sixteenths and seconds might be called frequently,
    // this value is precalculated to spare a few CPU cycles.  This value is actually determined
    // by ((1/lower) / (1/4)), since a quarter note has a value of 1/4 bar at 4/4 time.  By
    // applying this adjustment factor, any time signature can easily be converted to 4/4 time.
    m_quarter_factor = (4.0 / m_lower);
  }
}

void eventManager::update(unsigned long ticks) {
  for(std::vector<tEvent*>::iterator iter = m_events.begin(); iter != m_events.end();) {
    // Subtract ticks from this event
    (*iter)->ticks -= ticks;
    
    // If less than 0, then this event is ready to be dispatched
    if((*iter)->ticks <= 0) {
      (*iter)->listener->handleEvent((*iter)->data);
      
      // Free data and remove from the list of events
      if((*iter)->data != NULL) {
        free((*iter)->data);
      }
      iter = m_events.erase(iter);
    }
    else {
      // This event was not yet ready to be dispatched, so we just increment to the next one
      ++iter;
    }
  }
}
#endif