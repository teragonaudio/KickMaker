/*
 *  KickMakerCore.h
 *  KickMaker
 *
 *  Created by Nik Reiman on 04.02.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __KickMakerCore_H
#define __KickMakerCore_H

#ifndef __defaults_H
#include "defaults.h"
#endif

#ifndef __pluginCore_H
#include "pluginCore.h"
#endif

#ifndef __eventManager_H
#include "eventManager.h"
#endif

#ifndef __fxADSR_H
#include "effects/Envelopes/fxADSR.h"
#endif

#ifndef __fxLopassFilter_H
#include "effects/Filters/fxLopassFilter.h"
#endif

#ifndef __fxJumpCutter_H
#include "effects/Envelopes/fxJumpCutter.h"
#endif

#ifndef __fxSelectWave_H
#include "effects/Waveforms/fxSelectWave.h"
#endif

#ifndef __fxLFO_H
#include "effects/Waveforms/fxLFO.h"
#endif

#ifndef __fxAmplitudeCompressor_H
#include "effects/Gains/fxAmplitudeCompressor.h"
#endif

#ifndef __fxWhiteNosie_H
#include "effects/Misc/fxWhiteNoise.h"
#endif

#ifndef __KickMakerEditor_H
#include "KickMakerEditor.h"
#endif

class KickMakerCore : public pluginCore {
  public:
    KickMakerCore(int num_params, long version, const char *name);
    ~KickMakerCore();

    void loadPreset(int index);
    void noteOn(int note, int velocity);
    void noteOff(int note);
    void process(float **inputs, float **outputs, long frames);
    virtual void reset();
    virtual bool setParameter(int index, float value, bool override = false);
    virtual bool setParameterNormalized(int index, float value, bool override = false);
    void setVoice(int index);
    
  protected:
    struct tVoice {
      bool enabled;
      float freq;
      float freqbase;
      float freqrate;
      float volume;
      float phase;
      long index;
      
      fxADSR *adsr;
      fxWhiteNoise *noise;
      fxSelectWave *sinewave;
    };
private:
    struct tVoice m_voices[MAX_VOICES];
    
    fxLFO *m_lfos[MAX_LFOS];
    fxADSR *m_adsr;
    fxLopassFilter *m_lopass;
    fxAmplitudeCompressor *m_comp;
    fxJumpCutter *m_jump;
    
    bool m_unlocked;
    bool m_jump_on;
    
    float m_outputs[MAX_VOICES][MAX_FRAME_BUFFER];
    float m_scalers[MAX_VOICES];
    
    long m_note_off_post;
    long m_jump_index;
    
    int m_note_on;
};

#endif
