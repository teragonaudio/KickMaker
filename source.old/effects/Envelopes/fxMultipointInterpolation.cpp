/*
 *  fxMultipointInterpolation.cpp
 *  DualComp
 *
 *  Created by Nik Reiman on 03.07.07.
 *  Copyright 2007 Kemper Digital GmbH. All rights reserved.
 *
 */

#ifndef __fxMultipointInterpolation_H
#include "fxMultipointInterpolation.h"
#endif

fxMultipointInterpolation::fxMultipointInterpolation(pluginCore *p) : effectCore(p, fxMultipointInterpolation_NUM_PARAMS)
{
  // All calls made to setParameter after this will reallocate these buffers automatically
  effectCore::setParameter(fxMultipointInterpolation_NUM_POINTS, fxMultipointInterpolation_DEF_POINTS);
  m_y_values = new float[fxMultipointInterpolation_DEF_POINTS];
  m_x_values = new float[fxMultipointInterpolation_DEF_POINTS];
  
  memset(m_gain_values, 0x0, fxMultipointInterpolation_MAX_BUFFER);
  
  m_point_last = 0.0;
  m_point_cur = 0.0;
  m_point_next = 0.0;
  
  m_num_samples = 0;
  m_gain_values_max = 0;
  m_gain_values_index = 0;
}

fxMultipointInterpolation::~fxMultipointInterpolation()
{
  delete [] m_x_values;
  delete [] m_y_values;
}

float fxMultipointInterpolation::getGain()
{
  if(m_gain_values_index < m_gain_values_max)
  {
    return m_gain_values[m_gain_values_index++];
  }
  else
  {
    // printf("YOU FAIL IT %d, %d\n", m_gain_values_index, m_gain_values_max);
    return 0.0f;
    return m_gain_values[m_gain_values_max - 1];
  }
}

void fxMultipointInterpolation::process(float &input)
{
  m_point_last = m_point_cur;
  m_point_cur = m_point_next;
  m_point_next = fabs(input);
  ++m_num_samples;
  
  if(m_point_cur >= m_point_last && m_point_cur >= m_point_next && m_point_cur > DEF_DC_OFFSET)
  {
    // Rotate peak data (y values) and sample difference data between peaks (x values)
    int i;
    const int num_points = (int)getParameter(fxMultipointInterpolation_NUM_POINTS);
    for(i = 0; i < num_points - 1; ++i)
    {
      m_y_values[i] = m_y_values[i + 1];
      m_x_values[i] = m_x_values[i + 1];
    }
    m_y_values[num_points - 1] = m_point_cur;
    m_x_values[num_points - 1] = m_num_samples;
    m_x_values[0] = 0;
    
    // Calculate coefficients for multi-point polynomial interpolation
    // The general formula for this function is:
    // f(x) = sum(i = 0, i = n - 1, y_i * product(j = 0, j = n - 1 && j != i, (x - x_j) / (x_i - x_j)))
    // or, in other words:
    //       n-1      n-1
    // f(x) = ·  y_i * ¸ (x - x_j) / (x_i - x_j)
    //       i=0    j=0,j!=i
    //
    // For each iteration in the summation loop, we get a normal polynomial function with the form:
    // (x - a) * (x - b) * ... (x - n)
    // ...with a single coefficient multiplier for all terms.  Thus, we can collect the terms as such:
    // x^(n - 1) + x^(n - 2) * (a + b + ... n) + x^(n - 3) * (ab + ac + ... an + bc + bd + ... bn) + ... + (a * b * ... n)
    //
    // So we calculate these coefficients first, then store them in n buffer slots with each one multiplied by the
    // function coefficient.  After that, we are ready to collect terms and build a single polynomial function
    
    /* This code is temporarily disabled, because calculating the function coefficients for
       an arbitrary number of points is a HUGE BITCH, and probably will cost too much performance,
       So instead we will simply do it for 3 points, but leave the window open for future expansion here..
       
    float func_coeffs[num_points];
    float coeffs[num_points][num_points - 1];
    float terms[num_points];
    int j;
    for(i = 0; i < num_points; ++i)
    {
      func_coeffs[i] = m_y_values[i];
      // Gather the individual a, b, c, ... n terms and calculate the function coefficient
      for(j = 0; j < num_points; ++j)
      {
        if(i == j)
          continue;
        terms[i][j] = -1.0 * m_x_values[j];
        func_coeffs[i] /= (m_x_values[i] - m_x_values[j]);
      }
      
      // Calculate combined coefficients for each polynomial term
      float result;
      for(j = 0; j < num_terms; ++j)
      {
        for(int k = j; k > 0; --k)
        {
          // ARRRG, I don't know if it's possible to do this without some crazy ass recursion...
        }
        
        coeffs[i][j] = func_coeffs[j] * result;
      }
    }
    */
    
    // Calculate gain points for all values between last and current peak using generated polynomial
    m_gain_values_max = m_num_samples;
    int x = m_x_values[1];
    for(i = 0; i < m_num_samples && i < fxMultipointInterpolation_MAX_BUFFER; ++i, ++x)
    {
      // Ciao, bella!
      m_gain_values[i] = (m_y_values[0] / m_x_values[1] / m_x_values[2] + m_y_values[1] / m_x_values[1] /
                           (m_x_values[1]-m_x_values[2]) + m_y_values[2] / m_x_values[2] /
                           (m_x_values[2] - m_x_values[1])) * (x * x) +
                         (m_y_values[0] / m_x_values[1] / m_x_values[2] * 
                           (0.0 - m_x_values[1] - m_x_values[2]) -
                           m_y_values[1] / m_x_values[1] / (m_x_values[1] - m_x_values[2]) *
                           m_x_values[2] - m_y_values[2] / m_x_values[2] /
                           (m_x_values[2] - m_x_values[1]) * m_x_values[1]) * x +
                         m_y_values[0];
    }
    
    // Ready to go!
    m_gain_values_index = 0;
    m_num_samples = 0;
  }
}

void fxMultipointInterpolation::process(float *inputs, long frames)
{
  for(long i = 0; i < frames; ++i)
  {
    process(inputs[i]);
  }
}

void fxMultipointInterpolation::setParameter(int index, float value)
{
  if(index == fxMultipointInterpolation_NUM_POINTS)
  {
    // Disabled because setting this value arbitrarily is going to be painful
    return;
    
    if(value > 1.0)
    {
      if(m_x_values)
        delete [] m_x_values;
      m_x_values = new float[(int)value];
      
      if(m_y_values)
        delete [] m_x_values;
      m_y_values = new float[(int)value];
    }
    else
    {
      return;
    }
  }
  
  effectCore::setParameter(index, value);
}