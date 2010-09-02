/*
 *  effectCore.cpp - pluginCore
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
#include "effectCore.h"
#endif

effectCore::effectCore(pluginCore *p, int num_params)
{
  m_plugin = p;
  m_num_params = num_params;
  if(num_params)
  {
    m_params = new float*[num_params];
    m_local_params = new float[num_params];
    for(int i = 0; i < num_params; ++i)
    {
      m_local_params[i] = DEF_DC_OFFSET;
      m_params[i] = &m_local_params[i];
    }
  }
  else
  {
    m_params = 0;
    m_local_params = 0;
  }
}

effectCore::~effectCore()
{
  if(m_num_params)
  {
    delete [] m_params;
    delete [] m_local_params;
  }
}

float effectCore::getParameter(int index) const
{
  return *m_params[index];
}

void effectCore::linkParameter(int plugin_index, int effect_index)
{
  if(effect_index < m_num_params && effect_index >= 0)
  {
    m_params[effect_index] = &(m_plugin->m_params[plugin_index].value);
  }
}

void effectCore::linkParameter(float *target, int effect_index)
{
  if(effect_index < m_num_params && effect_index >= 0)
  {
    m_params[effect_index] = target;
  }
}

inline void effectCore::process(float *in_left, float *in_right, long frames)
{
  for(long i = 0; i < frames; ++i)
  {
    process(in_left[i]);
    process(in_right[i]);
  }
}

inline void effectCore::process(float *inputs, long frames)
{
  for(long i = 0; i < frames; ++i)
  {
    process(inputs[i]);
  }
}

void effectCore::setParameter(int index, float value)
{
  *m_params[index] = value;
}
#endif