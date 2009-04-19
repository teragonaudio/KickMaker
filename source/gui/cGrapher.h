/*
 *  cGrapher.h
 *  DualComp
 *
 *  Created by Nik Reiman on 03.12.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __cGrapher_H
#define __cGrapher_H

#ifndef __pluginCore_H
#include "pluginCore.h"
#endif

#ifndef __vstgui__
#include "vstgui.h"
#endif

typedef float (*fnGrapherCallbackPtr)(float in, pluginCore *p);

const CColor _DEF_TERAGON_ORANGE = { 255, 91, 15, 255 };

class cGrapher : public CControl {
public:
	cGrapher(const CRect &size, CControlListener *listener, long tag, CBitmap *background,
					 float x_lower, float x_upper, CColor color = _DEF_TERAGON_ORANGE);
	~cGrapher();
	
	virtual void draw(CDrawContext *dc);
	virtual void setBounds(int x_lower, int x_upper);
	virtual void setCallback(fnGrapherCallbackPtr call);
	virtual void setCore(pluginCore *p);
protected:
    CColor m_color;
		fnGrapherCallbackPtr m_callback;
  float *m_points;
	float m_x_lower, m_x_upper;
	float m_x_stepsize, m_y_stepsize ;
	pluginCore *m_core;
private:
};

#endif