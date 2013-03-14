/*
 *  effectCore.h - pluginCore
 *
 *  Created by Nik Reiman on 04.01.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 *  This source code may NOT be redistributed without express permission of Teragon Audio.  It may be used
 *  in free or commercial software works, but unauthorized duplication or resale in whole or part is
 *  strictly prohibited.
 */

#if USE_PC_EFFECTS
#ifndef __effectCore_H
#define __effectCore_H

#ifndef __pluginCore_H
#include "pluginCore.h"
#endif

#include <stdio.h>

/*! Macro for quick parameter access */
#define EPARAM(x) ( *m_params[x] )

/*! \class effectCore
* \brief Modular effect framewark which can be used within pluginCore
*
* EffectCore is an extension to PluginCore which provides recyclable "mini-effects" which can be
* shared between plugins.  An simple example of this might be a filter algorithm which would be useful in
* a number of different potential projects.  To maximize reusability across different projects, 
* effectCore objects were designed to be unaware of the plugin-specific settings, and to be modularly
* used in different plugins.
*
* \note To use effectCore support in your plugin, you must define the following preprocessor symbols:
* - USE_PC_EFFECTS
*
* To create an effect, simply create a new class which inherits from effectCore and overrides at least
* one of the effectCore::process() methods.  Each effect also has its own set of parameters, but in most
* cases it makes sense to "link" these parameters to those of the controlling plugin.  After the effect
* object has been initialized within its plugin host, then it must be told which of the plugin's parameters
* correspond to its internal parameter settings.  In the above example of a basic filter effect, the effect
* might only have two parameters, one for the filter's frequency, and the other for resonance.  Any plugin
* utilizing this effect will undoubtably have several additional parameters, but only needs to inform the
* effect which two of its parameters would correspond to the filter effect.  For more information on how
* parameter links are created, see the documentation for linkParameter().
*
* For safety purposes, when an effect is created, it contains an array of floating point values which
* parameters may be stored in.  The m_params structure actually only stores pointers to these array values,
* and when a parameter link is made, the address of the pointer is changed to point to the address of the
* variable in the hosting plugin.  This also means that effect parameters do not need to be explicitly
* linked within the plugin.  In the example filter effect, there could also be a parameter for filter type
* (ie, hipass, lopass, bandpass, etc.).  In some situations, it may not make sense to attach this value
* to a parameter within the plugin which the user could freely modify, so this parameter could be left
* unlinked, and then manually set by the plugin by calling effectCore::setParameter().
*
* So, each effect should define its own set of parameters (in an enumerated list or something similar),
* and parameter links should be created directly after the effect object is initialized in the plugin's
* constructor.
*
* Within the effectCore object itself, the structure is very similar to a simplified pluginCore object.
* However, two overrides are given for the effectCore::process() implementation, one being to directly
* process a single frame, and the other to process a number of frames.  In both cases, the effect is
* expected to directly modify the input data.
*/
class effectCore
{
public:
  /*! \brief Create a new effect
  * \param *p The pluginCore object which this effect is attached to
  * \param num_params The number of parameters the effect uses.  This is \b not
  * the same as the number of parameters being used by the pluginCore parent object.
  */
  effectCore(pluginCore *p, int num_params);
  virtual ~effectCore();
  
  /*! \brief Gets the value of a parameter
    * \param index The parameter index to retrieve
    *
    * In the interests of performance, <b>this method does no bounds checking</b>, nor does it check
    * to see if the parameters have been properly linked before retrieving their value.  It is the
    * responsibility of the programmer to correctly link all of the parameters for effects before
    * using them, or else segfaults will very likely occur.
    *
    * effectCore objects now also maintain their own parameter lists (see effectCore::m_params), so
    * one can directly access parameters this way if desired.
    */
  virtual float getParameter(int index) const;
  
  /*! \brief Associate an internal parameter with a parameter from the pluginCore parent object
    * \param plugin_index The index of the pluginCore parameter to link
    * \param effect_index The index of the effectCore parameter to use for the link
    *
    * This method is what makes parameters in effectCore objects work.  Ideally, the pluginCore parent
    * object should insubstantiate all of the effectCore objects in its constructor, and then call
    * this method to create parameter links for all of the appropriate parameters.  So, only the
    * pluginCore object needs to be aware of the parameters that the individual effectCore class
    * will be expecting, and it should create parameters for those if necessary.  In this way,
    * individual effect classes can be reused between plugins without any modification to the
    * actual code.
    *
    * effectCore also maintains local parameter lists, and when this method is called, a pointer is
    * passed to the master pluginCore object to associate the two.  When pluginCore::setParameter() or
    * pluginCore::setParameterNormalized() is called, then the m_params objects will be updated, too.
    */
  virtual void linkParameter(int plugin_index, int effect_index);
  
  virtual void linkParameter(float *target, int effect_index);
  
  /*! \brief Stereo processing function
    * \param *in_left Left channel
    * \param *in_right Right channel
    * \param frames The number of framse to process
    *
    * Unless overridden, this method will loop over each frame and call process(float &input).
    */
  virtual void process(float *in_left, float *in_right, long frames);
  
  /*! \brief Mono processing function
    * \param *inputs An array of floating point values to directly modify
    * \param frames The number of frames in the inputs array
    *
    * Unless overridden, this method will loop over each frame and call process(float &input).
    */
  virtual void process(float *inputs, long frames);
  
  /*! \brief Single input processing function
    * \param &input The input value
    *
    * This method is designed to be run from within a plugin's processing loop.  It should contain
    * the 'heart' of your effect, and left as an inline function to be accessed from other process()
    * overrides you wish to implement.
    */
  virtual void process(float &input) {};
  
  /*! \brief Set a parameter value in the effect
    * \param index The parameter index
    * \param value The value to set the parameter to
    *
    * This method is designed to provide an easy way to set \b unlinked parameters.  Parameters that
    * are linked will point directly to the parameter variable of their master plugin, and thus do
    * not need to be manually set with this method.
    *
    * \note This method performs <b>no bounds checking</b>, so use with care!
    */
  virtual void setParameter(int index, float value);
  
protected:
  /*! Pointer to master plugin. */
  pluginCore *m_plugin;
  /*! Array of pointers to actual parameters.  When linked, these will point to the parameters of
    * the master plugin.  Otherwise, they will point to the respectively indexed values in
    * m_local_params. */
  float **m_params;
  /*! Array with "local" parameters for the effect.  These are provided namely as a safety measure against
    * unlinked parameters. */
  float *m_local_params;
  /*! Number of parameters in the effect. */
  int m_num_params;
  
private:
};

#endif
#endif