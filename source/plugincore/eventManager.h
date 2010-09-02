/*
 *  eventManager.h - pluginCore
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
#define __eventManager_H

#include <time.h>

#include <vector>

/*! \class eventListener
* \brief Base class for an object which will receive event notifications from an eventManager object
*
* Inherit from this class to create an object capable of being notified by the event listener.
*/
class eventListener {
public:
  eventListener() {};
  virtual ~eventListener() {};
  
  /*! \brief Method to be called when the object receives notifications
    * \param data Pointer to data passed in during addEvent() (if given).  You are responsible for
    * freeing this data when finished with it.
    */
  virtual void handleEvent(void *data = 0) = 0;
protected:
private:
};

/*! \class eventManager
* \brief Flexible event management and object notification class.
*
* PluginCore can use the eventManager class as a local event manager, which is used to schedule events
* based on frames.  In the case of MIDI events or parameter changes, some hosts will ask the plugin
* to act on these events in a certain number of frames (rather than immediately).  The eventManager
* class can be used in this fashion to allow the plugin to schedule these events for a frame offset,
* and then act on them when appropriate.  The manager object may schedule events for any number of
* eventListener objects.
*
* \warning In order to use this functionality correctly, one \b must call the base pluginCore::process()
* at the beginning of the processing method.  Otherwise, all MIDI events will be scheduled and never
* actually acted upon!
*
* \note To enable eventManager in your plugin, the following preprocessor symbols must be defined:
* - USE_PC_EVENTS
*
* The actual eventManager implementation is based simply on the concept of "ticks" which can be
* an arbitrary measure of time.  When used within PluginCore itself, the ticks unit is in sample frames.
* However, in some cases, it may make sense to use seconds or some other value for this unit.  The
* nature of this unit does not need to be explicitly specified within the eventManager object; instead,
* it simply expects that the values given to it in update() will represent an increasing quantity.
*
* The eventManager class also provides the functionality to schedule events in terms of ticks or in
* bars/beats/sixteenths.  If you wish to schedule events in terms of musical time, then the setBPM(),
* setSampleRate(), and setTimeSignature() methods must be called before attempting to use addEvent(),
* and the tick units for the eventManager object must be in sample frames.
*/
class eventManager {
public:
  /*! \brief Create a new event manager object
  * \param ticks The inital value for the clock in ticks
  */
  eventManager() {};
  virtual ~eventManager() {};
  
  /*! \brief Add an event to the stack
    * \param el The listener object to be called
    * \param ticks Number of ticks to wait
    * \param data Data sent to the listener when event occurs (optional)
    * \param update Determines whether or not an event should be updated rather than scheduling another
    * event of the same type.  If set to true, then this method will first search through the event stack
    * to see if there is already an event with the same listener as the one passed in.  If so, the timer
    * for this event is set to be the new number of ticks, and the data for the event is also replaced.
    * If this value is false, and such an event already exists, then a new event is added to the stack.
    *
    * When an event is added here, it will be called in the number of ticks relative to when it was added.
    * The eventListener object's handleEvent() method will be called, and then removed from the stack of
    * events.  If an event is posted twice by the same event before the first call has timed out, then the
    * number of ticks will be added to the existing value for the listener.
    */
  virtual void addEvent(eventListener *el, long ticks, void *data = 0, bool update = true);

  /*! \brief Add an event to the stack based on musical time
    * \param el The listener object to be called
    * \param bars Number of bars to wait
    * \param beats Number of beats to wait
    * \param sixteenths Number of sixteenths to wait
    * \param data Data sent to the listener when event occurs (optional)
    * \param update Determines whether or not an event should be updated or a new event should be
    * scheduled.
    *
    * For more information about the scheduling behavior of this method, see
    * addEvent(eventListener *el, long ticks, void *data, bool update).
    */
  virtual void addEvent(eventListener *el, int bars, int beats, int sixteenths, void *data, bool update);
  
  /*! \brief Return the current number of ticks. */
  unsigned long getTicks() const;
  
  /*! \brief Set the tempo for the event manager
    * \param bpm The tempo in beats per minute
    *
    * This method is only needed if you wish to schedule events based on bars/beats/sixteenths.  The
    * method should be called anytime before attempting to use addEvent().
    */
  virtual void setBPM(double bpm);
  
  /*! \brief Set the sample rate for the event manager
    * \param srate The sample rate in Hertz
    *
    * This method is only needed if you wish to schedule events based on bars/beats/sixteenths.  The
    * method should be called anytime before attempting to use addEvent().
    */
  virtual void setSampleRate(float srate);
  
  /*! \brief Set the time signature
    * \param upper The numerator (top number) of the time signature (must be greater or equal to one)
    * \param lower The denominator (bottom number) of the time signature (must be greater or equal to one)
    *
    * This method is only needed if you wish to schedule events based on bars/beats/sixteenths.  The
    * method should be called anytime before attempting to use addEvent().
    */
  virtual void setTimeSignature(double upper, double lower);

  /*! \brief Update all events with a given number of ticks, and send notifications to those which have
    * timed out.  This should be called in the idle() method (when used to manage GUI events and such),
    * or in the process() method when used in a plugin.
    * \param ticks The current tick unit count, which may be expressed as the current number of seconds,
    * beats, samples, etc.  The actual units of this quantity are not important, so long as the data passed
    * into this method increases with each subsequent call.  However, PluginCore itself uses sample count
    * for this quantity.
    */
  virtual void update(unsigned long ticks);
  
  /*! \brief Structure used to store events in the event stack */
  typedef struct {
    /*! Listener object */
    eventListener *listener;
    /*! Number of ticks */
    long ticks;
    /*! Arbitrary user data (is automatically freed after event is dispatched) */
    void *data;
  } tEvent;
protected:
  /*! The event stack */
  std::vector<tEvent*> m_events;
  /*! Tempo in beats per minute (only relevant when wanting to schedule events by musical time) */
  double m_bpm;
  /*! Time signature's upper value (only relevant when scheduling events by musical time) */
  double m_upper;
  /*! Time signature's lower value (only relevant when scheduling events by musical time) */
  double m_lower;
  /*! Weight of a quarter note, determined by the m_upper and m_lower values (only relevant when
    * scheduling events by musical time) */
  double m_quarter_factor;
  /*! Sample rate of the plugin (only relevant when scheduling events by musical time) */
  float m_sample_rate;
private:
};

#endif
#endif