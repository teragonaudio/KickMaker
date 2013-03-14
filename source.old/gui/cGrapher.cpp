/*
 *  cGrapher.cpp
 *  DualComp
 *
 *  Created by Nik Reiman on 03.12.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __cGrapher_H
#include "cGrapher.h"
#endif

cGrapher::cGrapher(const CRect &size, CControlListener *listener, long tag, CBitmap *background,
									 float x_lower, float x_upper, CColor color) :
CControl(size, listener, tag, background) {
  m_points = 0;
	setBounds(x_lower, x_upper);
  m_color = color;
}

cGrapher::~cGrapher() {
  if(m_points) {
    delete [] m_points;
  }
}

void cGrapher::draw(CDrawContext *dc) {
	dc->setDrawMode(kAntialias);
	dc->setFrameColor(m_color);
	dc->setLineWidth(1);
	
	CPoint point(size.left, size.top);
	dc->moveTo(point);
	
  float lowest = 1.0;
  float highest = 0;
  float ycoord = 0;
  
	for(int i = 0; i < size.width(); ++i) {
		ycoord = m_callback((float)i * m_x_stepsize, m_core);
		if(ycoord < lowest) {
      lowest = ycoord;
    }
    else if(ycoord > highest) {
      highest = ycoord;
    }
    
    m_points[i] = ycoord;
  }
  
  float yscale = (float)size.height() / (highest - lowest);
  for(int i = 0; i < size.width(); ++i) {
    point(size.left + i, size.bottom - (yscale * m_points[i]));
    dc->lineTo(point);
    dc->moveTo(point);
  }
    
	setDirty(false);
}

void cGrapher::setBounds(int x_lower, int x_upper) {
	m_x_lower = x_lower;
	m_x_upper = x_upper;
  m_x_stepsize = (float)(m_x_upper - m_x_lower) / (float)size.width();
  if(m_points) {
    delete [] m_points;
  }
  m_points = new float[size.width()];
}

void cGrapher::setCallback(fnGrapherCallbackPtr call) {
	m_callback = call;
}

void cGrapher::setCore(pluginCore *p) {
	m_core = p;
}