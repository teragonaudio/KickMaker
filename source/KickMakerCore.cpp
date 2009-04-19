/*
 *  KickMakerCore.cpp
 *  KickMaker
 *
 *  Created by Nik Reiman on 04.02.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __KickMakerCore_H
#include "KickMakerCore.h"
#endif

#ifndef __productDir_H
#include "productDir.h"
#endif

#include <stdio.h>
#include <math.h>

KickMakerCore::KickMakerCore(int num_params, long version, char *name) :
pluginCore(num_params, version, name) {
  addParameter(PRM_1_ENABLED, "Osc 1 On", TYP_BOOL, 0.0, 1.0, 1.0);
  addParameter(PRM_1_FREQ, "Freq 1", TYP_HZ, MIN_FREQ, MAX_FREQ, MIN_FREQ);
  addParameter(PRM_1_FREQ_FINE, "Freq 1 Fine", TYP_HZ, -1.0, 1.0, 0.0);
  addParameter(PRM_1_FREQ_EXPAND, "Freq 1 Expand", TYP_PERCENT, 0.0, 100.0, 0.0);
  addParameter(PRM_1_FREQ_EXPAND_RATE, "Freq 1 Expand Rate", TYP_MILLISECONDS,
               1.0, MAX_FREQ_EXPAND_RATE, 1.0);
  addParameter(PRM_1_PHASE, "Phase 1", TYP_GENERIC, 0.0, MAX_PHASE, 0.0);
  addParameter(PRM_1_NOISE, "Noise 1", TYP_GENERIC, 0.0, MAX_NOISE, 0.0);
  addParameter(PRM_1_ATTACK, "Attack 1", TYP_GENERIC, MIN_ATTACK, MAX_ATTACK, DEF_ATTACK);
  addParameter(PRM_1_ATTACK_AMP, "Attack Amp 1", TYP_GENERIC, 0.0, 1.0, DEF_ATTACK_AMP);
  addParameter(PRM_1_DECAY, "Decay 1", TYP_GENERIC, 0.01, MAX_DECAY, DEF_DECAY);
  addParameter(PRM_1_DECAY_AMP, "Decay Amp 1", TYP_GENERIC, 0.0, 1.0, DEF_DECAY_AMP);
  addParameter(PRM_1_SUSTAIN, "Sustain 1", TYP_GENERIC, 0.01, MAX_SUSTAIN, DEF_SUSTAIN);
  addParameter(PRM_1_SUSTAIN_AMP, "Sustain Amp 1", TYP_GENERIC, 0.0, 1.0, DEF_SUSTAIN_AMP);
  addParameter(PRM_1_RELEASE, "Release 1", TYP_GENERIC, MIN_RELEASE, MAX_RELEASE, DEF_RELEASE);
  addParameter(PRM_1_VOLUME, "Volume 1", TYP_DB, MIN_VOL, MAX_VOL, MAX_VOL);
  
  addParameter(PRM_2_ENABLED, "Osc 2 On", TYP_BOOL, 0.0, 1.0, 0.0);
  addParameter(PRM_2_FREQ, "Freq 2", TYP_HZ, MIN_FREQ, MAX_FREQ, MIN_FREQ);
  addParameter(PRM_2_FREQ_FINE, "Freq 2 Fine", TYP_HZ, -1.0, 1.0, 0.0);
  addParameter(PRM_2_FREQ_EXPAND, "Freq 2 Expand", TYP_PERCENT, 0.0, 100.0, 0.0);
  addParameter(PRM_2_FREQ_EXPAND_RATE, "Freq 2 Expand Rate", TYP_MILLISECONDS,
               1.0, MAX_FREQ_EXPAND_RATE, 1.0);
  addParameter(PRM_2_PHASE, "Phase 2", TYP_GENERIC, 0.0, MAX_PHASE, 0.0);
  addParameter(PRM_2_NOISE, "Noise 2", TYP_GENERIC, 0.0, MAX_NOISE, 0.0);
  addParameter(PRM_2_ATTACK, "Attack 2", TYP_GENERIC, MIN_ATTACK, MAX_ATTACK, DEF_ATTACK);
  addParameter(PRM_2_ATTACK_AMP, "Attack Amp 2", TYP_GENERIC, 0.0, 1.0, DEF_ATTACK_AMP);
  addParameter(PRM_2_DECAY, "Decay 2", TYP_GENERIC, 0.01, MAX_DECAY, DEF_DECAY);
  addParameter(PRM_2_DECAY_AMP, "Decay Amp 2", TYP_GENERIC, 0.0, 1.0, DEF_DECAY_AMP);
  addParameter(PRM_2_SUSTAIN, "Sustain 2", TYP_GENERIC, 0.01, MAX_SUSTAIN, DEF_SUSTAIN);
  addParameter(PRM_2_SUSTAIN_AMP, "Sustain Amp 2", TYP_GENERIC, 0.0, 1.0, DEF_SUSTAIN_AMP);
  addParameter(PRM_2_RELEASE, "Release 2", TYP_GENERIC, MIN_RELEASE, MAX_RELEASE, DEF_RELEASE);
  addParameter(PRM_2_VOLUME, "Volume 2", TYP_DB, MIN_VOL, MAX_VOL, MAX_VOL);
  
  addParameter(PRM_3_ENABLED, "Osc 3 On", TYP_BOOL, 0.0, 1.0, 0.0);
  addParameter(PRM_3_FREQ, "Freq 3", TYP_HZ, MIN_FREQ, MAX_FREQ, MIN_FREQ);
  addParameter(PRM_3_FREQ_FINE, "Freq 3 Fine", TYP_HZ, -1.0, 1.0, 0.0);
  addParameter(PRM_3_FREQ_EXPAND, "Freq 3 Expand", TYP_PERCENT, 0.0, 100.0, 0.0);
  addParameter(PRM_3_FREQ_EXPAND_RATE, "Freq 3 Expand Rate", TYP_MILLISECONDS,
               1.0, MAX_FREQ_EXPAND_RATE, 1.0);
  addParameter(PRM_3_PHASE, "Phase 3", TYP_GENERIC, 0.0, MAX_PHASE, 0.0);
  addParameter(PRM_3_NOISE, "Noise 3", TYP_GENERIC, 0.0, MAX_NOISE, 0.0);
  addParameter(PRM_3_ATTACK, "Attack 3", TYP_GENERIC, MIN_ATTACK, MAX_ATTACK, DEF_ATTACK);
  addParameter(PRM_3_ATTACK_AMP, "Attack Amp 3", TYP_GENERIC, 0.0, 1.0, DEF_ATTACK_AMP);
  addParameter(PRM_3_DECAY, "Decay 3", TYP_GENERIC, 0.01, MAX_DECAY, DEF_DECAY);
  addParameter(PRM_3_DECAY_AMP, "Decay Amp 3", TYP_GENERIC, 0.0, 1.0, DEF_DECAY_AMP);
  addParameter(PRM_3_SUSTAIN, "Sustain 3", TYP_GENERIC, 0.01, MAX_SUSTAIN, DEF_SUSTAIN);
  addParameter(PRM_3_SUSTAIN_AMP, "Sustain Amp 3", TYP_GENERIC, 0.0, 1.0, DEF_SUSTAIN_AMP);
  addParameter(PRM_3_RELEASE, "Release 3", TYP_GENERIC, MIN_RELEASE, MAX_RELEASE, DEF_RELEASE);
  addParameter(PRM_3_VOLUME, "Volume 3", TYP_DB, MIN_VOL, MAX_VOL, MAX_VOL);
  
  addParameter(PRM_4_ENABLED, "Osc 4 On", TYP_BOOL, 0.0, 1.0, 0.0);
  addParameter(PRM_4_FREQ, "Freq 4", TYP_HZ, MIN_FREQ, MAX_FREQ, MIN_FREQ);
  addParameter(PRM_4_FREQ_FINE, "Freq 4 Fine", TYP_HZ, -1.0, 1.0, 0.0);
  addParameter(PRM_4_FREQ_EXPAND, "Freq 4 Expand", TYP_PERCENT, 0.0, 100.0, 0.0);
  addParameter(PRM_4_FREQ_EXPAND_RATE, "Freq 4 Expand Rate", TYP_MILLISECONDS,
               1.0, MAX_FREQ_EXPAND_RATE, 1.0);
  addParameter(PRM_4_PHASE, "Phase 4", TYP_GENERIC, 0.0, MAX_PHASE, 0.0);
  addParameter(PRM_4_NOISE, "Noise 4", TYP_GENERIC, 0.0, MAX_NOISE, 0.0);
  addParameter(PRM_4_ATTACK, "Attack 4", TYP_GENERIC, MIN_ATTACK, MAX_ATTACK, DEF_ATTACK);
  addParameter(PRM_4_ATTACK_AMP, "Attack Amp 4", TYP_GENERIC, 0.0, 1.0, DEF_ATTACK_AMP);
  addParameter(PRM_4_DECAY, "Decay 4", TYP_GENERIC, 0.01, MAX_DECAY, DEF_DECAY);
  addParameter(PRM_4_DECAY_AMP, "Decay Amp 4", TYP_GENERIC, 0.0, 1.0, DEF_DECAY_AMP);
  addParameter(PRM_4_SUSTAIN, "Sustain 4", TYP_GENERIC, 0.01, MAX_SUSTAIN, DEF_SUSTAIN);
  addParameter(PRM_4_SUSTAIN_AMP, "Sustain Amp 4", TYP_GENERIC, 0.0, 1.0, DEF_SUSTAIN_AMP);
  addParameter(PRM_4_RELEASE, "Release 4", TYP_GENERIC, MIN_RELEASE, MAX_RELEASE, DEF_RELEASE);
  addParameter(PRM_4_VOLUME, "Volume 4", TYP_DB, MIN_VOL, MAX_VOL, MAX_VOL);
  
  addParameter(PRM_ALL_ATTACK, "Global Attack", TYP_GENERIC, MIN_ATTACK, MAX_ATTACK, DEF_ATTACK);
  addParameter(PRM_ALL_ATTACK_AMP, "Global Attack Amp", TYP_GENERIC, 0.0, 1.0, DEF_ATTACK_AMP);
  addParameter(PRM_ALL_DECAY, "Global Decay", TYP_GENERIC, 0.01, MAX_DECAY, DEF_DECAY);
  addParameter(PRM_ALL_DECAY_AMP, "Global Decay Amp", TYP_GENERIC, 0.0, 1.0, DEF_DECAY_AMP);
  addParameter(PRM_ALL_SUSTAIN, "Global Sustain", TYP_GENERIC, 0.01, MAX_SUSTAIN, DEF_SUSTAIN);
  addParameter(PRM_ALL_SUSTAIN_AMP, "Global Sustain Amp", TYP_GENERIC, 0.0, 1.0, DEF_SUSTAIN_AMP);
  addParameter(PRM_ALL_RELEASE, "Global Release", TYP_GENERIC, MIN_RELEASE, MAX_RELEASE, DEF_RELEASE);
  addParameter(PRM_ALL_VOLUME, "Global Volume", TYP_DB, MIN_VOL, MAX_VOL, MAX_VOL);
  
  addParameter(PRM_COMP_ATTACK, "Comp Attack", TYP_MILLISECONDS,
               MIN_COMP_ATTACK, MAX_COMP_ATTACK, MIN_COMP_ATTACK);
  addParameter(PRM_COMP_RELEASE, "Comp Release", TYP_MILLISECONDS,
               MIN_COMP_RELEASE, MAX_COMP_RELEASE, MIN_COMP_RELEASE);
  addParameter(PRM_COMP_RATIO, "Comp Ratio", TYP_DB,
               MIN_COMP_RATIO, MAX_COMP_RATIO, MIN_COMP_RATIO);
  addParameter(PRM_COMP_THRESH, "Comp Thresh", TYP_DB,
               MIN_COMP_THRESH, MAX_COMP_THRESH, MAX_COMP_THRESH);
  
  addParameter(PRM_LOPASS_FREQ, "Filter Freq", TYP_HZ_LOG, MIN_FILTER_FREQ, MAX_FILTER_FREQ, MAX_FILTER_FREQ);
  addParameter(PRM_LOPASS_RESONANCE, "Filter Resonance", TYP_GENERIC, 0.1, sqrt(2.0), 1.0);
  
  addParameter(PRM_1_WAVE_TYPE, "Wave Type 1", TYP_GENERIC, 0, 3, 0);
  addParameter(PRM_2_WAVE_TYPE, "Wave Type 2", TYP_GENERIC, 0, 3, 0);
  addParameter(PRM_3_WAVE_TYPE, "Wave Type 3", TYP_GENERIC, 0, 3, 0);
  addParameter(PRM_4_WAVE_TYPE, "Wave Type 4", TYP_GENERIC, 0, 3, 0);
  
#if FEATURE_LFO
  addParameter(PRM_LFO_1_ENABLE, "LFO 1 Enable", TYP_BOOL, 0, 1, 0);
  addParameter(PRM_LFO_1_RATE, "LFO 1 Rate", TYP_GENERIC, 4.0, 25.0, 4.0);
  addParameter(PRM_LFO_1_AMOUNT, "LFO 1 Amount", TYP_GENERIC, 0.0, 1.0, 1.0);
  addParameter(PRM_LFO_1_TARGET, "LFO 1 Target", TYP_GENERIC, 0, PRM_LOPASS_RESONANCE, 0);
  
  addParameter(PRM_LFO_2_ENABLE, "LFO 2 Enable", TYP_BOOL, 0, 1, 0);
  addParameter(PRM_LFO_2_RATE, "LFO 2 Rate", TYP_GENERIC, 4.0, 25.0, 4.0);
  addParameter(PRM_LFO_2_AMOUNT, "LFO 2 Amount", TYP_GENERIC, 0.0, 1.0, 1.0);
  addParameter(PRM_LFO_2_TARGET, "LFO 2 Target", TYP_GENERIC, 0, PRM_LOPASS_RESONANCE, 0);
 
  addParameter(PRM_LFO_3_ENABLE, "LFO 3 Enable", TYP_BOOL, 0, 1, 0);
  addParameter(PRM_LFO_3_RATE, "LFO 3 Rate", TYP_GENERIC, 4.0, 25.0, 4.0);
  addParameter(PRM_LFO_3_AMOUNT, "LFO 3 Amount", TYP_GENERIC, 0.0, 1.0, 1.0);
  addParameter(PRM_LFO_3_TARGET, "LFO 3 Target", TYP_GENERIC, 0, PRM_LOPASS_RESONANCE, 0);
#endif
  
  addParameter(PRM_SAMPLE_RATE, "Sample Rate", TYP_HZ, 32000, 96000, 44100, true);
  
  // m_logger->logS(1000);
  m_adsr = new fxADSR(this);
  m_adsr->linkParameter(PRM_ALL_ATTACK, fxADSR_PRM_ATTACK);
  m_adsr->linkParameter(PRM_ALL_ATTACK_AMP, fxADSR_PRM_ATTACK_AMP);
  m_adsr->linkParameter(PRM_ALL_DECAY, fxADSR_PRM_DECAY);
  m_adsr->linkParameter(PRM_ALL_DECAY_AMP, fxADSR_PRM_DECAY_AMP);
  m_adsr->linkParameter(PRM_ALL_SUSTAIN, fxADSR_PRM_SUSTAIN);
  m_adsr->linkParameter(PRM_ALL_SUSTAIN_AMP, fxADSR_PRM_SUSTAIN_AMP);
  m_adsr->linkParameter(PRM_ALL_RELEASE, fxADSR_PRM_RELEASE);
  m_adsr->linkParameter(PRM_SAMPLE_RATE, fxADSR_PRM_SAMPLE_RATE);
  m_adsr->recache();
  
  // m_logger->logS(1001);
  m_comp = new fxAmplitudeCompressor(this);
  m_comp->linkParameter(PRM_COMP_ATTACK, fxAmplitudeCompressor_PRM_ATTACK_GAIN);
  m_comp->linkParameter(PRM_COMP_RELEASE, fxAmplitudeCompressor_PRM_RELEASE);
  m_comp->linkParameter(PRM_COMP_RATIO, fxAmplitudeCompressor_PRM_RATIO);
  m_comp->linkParameter(PRM_COMP_THRESH, fxAmplitudeCompressor_PRM_ATTACK_SHAPE);
  
  // m_logger->logS(1035);
  m_lopass = new fxLopassFilter(this);
  m_lopass->linkParameter(PRM_LOPASS_FREQ, fxLopassFilter_PRM_FREQ);
  m_lopass->linkParameter(PRM_LOPASS_RESONANCE, fxLopassFilter_PRM_RESONANCE);
  m_lopass->linkParameter(PRM_SAMPLE_RATE, fxLopassFilter_PRM_SAMPLE_RATE);
  m_lopass->recache();
  
  // m_logger->logS(1002);
  m_jump = new fxJumpCutter(this);
  
  for(int i = 0; i < MAX_VOICES; ++i) {
    // m_logger->logD(1003, i);
    m_voices[i].enabled = false;
    m_voices[i].freq = 0;
    m_voices[i].freqbase = 0;
    m_voices[i].freqrate = 0.0;
    m_voices[i].volume = 1.0;
    m_voices[i].index = 0;
    m_voices[i].phase = 0.0;
    m_voices[i].adsr = new fxADSR(this);
    m_voices[i].noise = new fxWhiteNoise(this);
    
    m_voices[i].sinewave = new fxSelectWave(this);
    // Because of the way that this is set up, we need to establish links for all the individual
    // subwaves in this structure
    for(int wav = 0; wav < WAV_LAST_WAV; ++wav)
    {    
      m_voices[i].sinewave->setType(wav);
      m_voices[i].sinewave->linkParameter(PRM_SAMPLE_RATE, fxSinewave_PRM_SAMPLE_RATE);
      m_voices[i].sinewave->linkParameter(&m_voices[i].freq, fxSinewave_PRM_FREQ);
      m_voices[i].sinewave->linkParameter(&m_voices[i].phase, fxSinewave_PRM_PHASE);
    }
    m_voices[i].sinewave->setType(WAV_SINE);
  }
  
  // Voices 1 is on by default, so we must manually enable them here
  m_voices[0].enabled = true;
  // pluginCore::m_num_samples_processed = 0;
  m_note_off_post = 0;
  m_note_on = 0;
  m_jump_on = false;
  m_jump_index = 0;
  
  // Load presets; system first, then user
  char pdir[MAX_DIR];
#ifdef MAC
  if(getPluginBundleDir(DEF_BUNDLE_IDENT, (char*)&pdir)) {
    strcat(pdir, "/Contents/Resources/Presets/");
    slurpDirectory(pdir);
  }
#endif
  
  if(getProductDir(DEF_PRODUCT, (char*)&pdir)) {
    slurpDirectory(pdir);
  }
  
  // m_logger->logS(1004);
  m_voices[0].adsr->linkParameter(PRM_1_ATTACK, fxADSR_PRM_ATTACK);
  m_voices[0].adsr->linkParameter(PRM_1_ATTACK_AMP, fxADSR_PRM_ATTACK_AMP);
  m_voices[0].adsr->linkParameter(PRM_1_DECAY, fxADSR_PRM_DECAY);
  m_voices[0].adsr->linkParameter(PRM_1_DECAY_AMP, fxADSR_PRM_DECAY_AMP);
  m_voices[0].adsr->linkParameter(PRM_1_SUSTAIN, fxADSR_PRM_SUSTAIN);
  m_voices[0].adsr->linkParameter(PRM_1_SUSTAIN_AMP, fxADSR_PRM_SUSTAIN_AMP);
  m_voices[0].adsr->linkParameter(PRM_1_RELEASE, fxADSR_PRM_RELEASE);
  m_voices[0].adsr->linkParameter(PRM_SAMPLE_RATE, fxADSR_PRM_SAMPLE_RATE);
  m_voices[0].adsr->recache();
  m_voices[0].noise->linkParameter(PRM_1_NOISE, fxWhiteNoise_PRM_NOISE_LEVEL);
  
  m_voices[1].adsr->linkParameter(PRM_2_ATTACK, fxADSR_PRM_ATTACK);
  m_voices[1].adsr->linkParameter(PRM_2_ATTACK_AMP, fxADSR_PRM_ATTACK_AMP);
  m_voices[1].adsr->linkParameter(PRM_2_DECAY, fxADSR_PRM_DECAY);
  m_voices[1].adsr->linkParameter(PRM_2_DECAY_AMP, fxADSR_PRM_DECAY_AMP);
  m_voices[1].adsr->linkParameter(PRM_2_SUSTAIN, fxADSR_PRM_SUSTAIN);
  m_voices[1].adsr->linkParameter(PRM_2_SUSTAIN_AMP, fxADSR_PRM_SUSTAIN_AMP);
  m_voices[1].adsr->linkParameter(PRM_2_RELEASE, fxADSR_PRM_RELEASE);
  m_voices[1].adsr->linkParameter(PRM_SAMPLE_RATE, fxADSR_PRM_SAMPLE_RATE);
  m_voices[1].adsr->recache();
  m_voices[1].noise->linkParameter(PRM_2_NOISE, fxWhiteNoise_PRM_NOISE_LEVEL);
  
  m_voices[2].adsr->linkParameter(PRM_3_ATTACK, fxADSR_PRM_ATTACK);
  m_voices[2].adsr->linkParameter(PRM_3_ATTACK_AMP, fxADSR_PRM_ATTACK_AMP);
  m_voices[2].adsr->linkParameter(PRM_3_DECAY, fxADSR_PRM_DECAY);
  m_voices[2].adsr->linkParameter(PRM_3_DECAY_AMP, fxADSR_PRM_DECAY_AMP);
  m_voices[2].adsr->linkParameter(PRM_3_SUSTAIN, fxADSR_PRM_SUSTAIN);
  m_voices[2].adsr->linkParameter(PRM_3_SUSTAIN_AMP, fxADSR_PRM_SUSTAIN_AMP);
  m_voices[2].adsr->linkParameter(PRM_3_RELEASE, fxADSR_PRM_RELEASE);
  m_voices[2].adsr->linkParameter(PRM_SAMPLE_RATE, fxADSR_PRM_SAMPLE_RATE);
  m_voices[2].adsr->recache();
  m_voices[2].noise->linkParameter(PRM_3_NOISE, fxWhiteNoise_PRM_NOISE_LEVEL);
  
  m_voices[3].adsr->linkParameter(PRM_4_ATTACK, fxADSR_PRM_ATTACK);
  m_voices[3].adsr->linkParameter(PRM_4_ATTACK_AMP, fxADSR_PRM_ATTACK_AMP);
  m_voices[3].adsr->linkParameter(PRM_4_DECAY, fxADSR_PRM_DECAY);
  m_voices[3].adsr->linkParameter(PRM_4_DECAY_AMP, fxADSR_PRM_DECAY_AMP);
  m_voices[3].adsr->linkParameter(PRM_4_SUSTAIN, fxADSR_PRM_SUSTAIN);
  m_voices[3].adsr->linkParameter(PRM_4_SUSTAIN_AMP, fxADSR_PRM_SUSTAIN_AMP);
  m_voices[3].adsr->linkParameter(PRM_4_RELEASE, fxADSR_PRM_RELEASE);
  m_voices[3].adsr->linkParameter(PRM_SAMPLE_RATE, fxADSR_PRM_SAMPLE_RATE);
  m_voices[3].adsr->recache();
  m_voices[3].noise->linkParameter(PRM_4_NOISE, fxWhiteNoise_PRM_NOISE_LEVEL);
  
#if FEATURE_LFO
  for(int i = 0; i < MAX_LFOS; ++i)
  {
    m_lfos[i] = new fxLFO(this);
    // Multiply by 4 here because there are 4 params per LFO
    m_lfos[i]->linkParameter(PRM_LFO_1_ENABLE + (i * 4), fxLFO_PRM_ENABLE);
    m_lfos[i]->linkParameter(PRM_LFO_1_RATE + (i * 4), fxLFO_PRM_FREQ);
    m_lfos[i]->linkParameter(PRM_LFO_1_AMOUNT + (i * 4), fxLFO_PRM_AMPLITUDE);
    m_lfos[i]->linkParameter(PRM_LFO_1_TARGET + (i * 4), fxLFO_PRM_TARGET);
    m_lfos[i]->linkParameter(PRM_SAMPLE_RATE, fxLFO_PRM_SAMPLE_RATE);
  }
#endif
}

KickMakerCore::~KickMakerCore() {
  // m_logger->logS(1006);
  for(int i = 0; i < MAX_VOICES; ++i) {
    delete m_voices[i].adsr;
    delete m_voices[i].noise;
  }
  delete m_adsr;
  delete m_comp;
}

void KickMakerCore::loadPreset(int index) {
  // TODO: Update the editor window somehow
  pluginCore::loadPreset(index);
}

void KickMakerCore::noteOn(int note, int velocity) {
  m_note_on = velocity;
  for(int i = 0; i < MAX_VOICES; ++i) {
    if(m_voices[i].enabled) {
      m_voices[i].index = 0;
      m_voices[i].adsr->reset();
      
      float rate = getParameter(REQ_VALUE_RAW, PRM_1_FREQ_EXPAND_RATE + ((PRM_1_VOLUME + 1) * i), NULL);
      float expand = getParameter(REQ_VALUE_RAW, PRM_1_FREQ_EXPAND + ((PRM_1_VOLUME + 1) * i), NULL);
      m_voices[i].freqbase = getMidiNoteTableFreq(note) + (getMidiNoteTableFreq(note) *
        (getParameter(REQ_VALUE_RAW, PRM_1_FREQ + ((PRM_1_VOLUME + 1) * i)) +
         getParameter(REQ_VALUE_RAW, PRM_1_FREQ_FINE + ((PRM_1_VOLUME + 1) * i))) / 100.0);
            
      if(expand && rate) {
        m_voices[i].freq = m_voices[i].freqbase + (m_voices[i].freqbase * MAX_FREQ_EXPAND *
                                                   (expand / 100.0));
        m_voices[i].freqrate = (m_voices[i].freq - m_voices[i].freqbase) /
          (rate * PARAM(PRM_SAMPLE_RATE) / 1000.0);
      }
      else {
        m_voices[i].freq = m_voices[i].freqbase;
        m_voices[i].freqrate = 0.0;
      }
    }
  }
  
  // This means that there is already a note playing, so then trigger the jump cutter
  if(m_note_off_post > 0) {
    m_jump_on = true;
  }
  
  m_adsr->reset();
  if(m_note_off_post < 0) {
    m_note_off_post = 0;
  }
  m_note_off_post += m_adsr->getLength();
  // m_logger->logD(1033, (int)m_note_off_post);
}

void KickMakerCore::noteOff(int note) {
}

void KickMakerCore::process(float **inputs, float **outputs, long frames) {
  float *out_left = outputs[0];
  float *out_right = outputs[1];

  pluginCore::process(inputs, outputs, frames);
  
#if FEATURE_LFO
  // Process LFO's
  for(int i = 0; i < MAX_LFOS; ++i)
  {
    if(getParameter(REQ_VALUE_RAW, PRM_LFO_1_ENABLE + (i * 4)))
    {
      m_lfos[i]->process(NULL, frames);
    }
  }
#endif
  
  float gain = (float)m_note_on * 0.00787402; // (1/127), midi max
  for(int i = 0; i < frames; ++i) {
    out_left[i] = 0.0;
    out_right[i] = 0.0;
    
    if(m_jump_on) {
      m_jump->setLength(DEF_NUM_JUMP_POINTS);
      m_jump_index = DEF_NUM_JUMP_POINTS;
      
      if(i) {
        m_jump->setBase(out_left[i - 1]);
      }
      else {
        m_jump->setBase(0.0);
      }
      
      m_jump->setIndex(0);
      m_jump->setTarget(0.0);
      m_jump_on = false;
    }
    
    if(m_note_off_post-- >= 0) {
      for(int j = 0; j < MAX_VOICES; ++j) {
        if(m_voices[j].enabled) {         
          m_scalers[j] = PARAM(PRM_SAMPLE_RATE) / m_voices[j].freq;        
          if(m_voices[j].index > m_scalers[j]) {
            m_voices[j].index = 0;
          }

          m_voices[j].sinewave->process(m_outputs[j][i]);
          
          if(m_voices[j].freq > m_voices[j].freqbase) {
            m_voices[j].freq -= m_voices[j].freqrate;
            m_scalers[j] = PARAM(PRM_SAMPLE_RATE) / m_voices[j].freq;
          }
          
          m_voices[j].noise->process(m_outputs[j][i]);
          m_voices[j].adsr->process(m_outputs[j][i]);
          out_left[i] += m_outputs[j][i] * gain * m_voices[j].volume;
        }
      }
      m_adsr->process(out_left[i]);
      
      if(m_jump_index) {
        m_jump->process(out_left[i]);
        --m_jump_index;
      }
    }
  }
  
  if(m_note_off_post > 0) {
    m_lopass->process(out_left, frames);
    for(int i = 0; i < frames; ++i) {
      m_comp->process(out_left[i]);
      out_left[i] *= PARAM(PRM_ALL_VOLUME);
      out_right[i] = out_left[i];
    }
  }
  else {
  }
}

void KickMakerCore::reset() {
}

bool KickMakerCore::setParameter(int index, float value, bool override) {
  if(pluginCore::setParameter(index, value, override)) {
    setVoice(index);
    if(index == PRM_LOPASS_FREQ || index == PRM_LOPASS_RESONANCE) {
      m_lopass->recache();
    }
    else if(index >= PRM_1_WAVE_TYPE && index <= PRM_4_WAVE_TYPE)
    {
      int voice_index = index - PRM_1_WAVE_TYPE;
      m_voices[voice_index].sinewave->setType((int)value);
    }
    return true;
  }
  else {
    return false;
  }
}

bool KickMakerCore::setParameterNormalized(int index, float value, bool override) {
  if(pluginCore::setParameterNormalized(index, value, override)) {
    setVoice(index);
    if(index == PRM_LOPASS_FREQ || index == PRM_LOPASS_RESONANCE) {
      m_lopass->recache();
    }
    else if(index >= PRM_1_WAVE_TYPE && index <= PRM_4_WAVE_TYPE)
    {
      int voice_index = index - PRM_1_WAVE_TYPE;
      m_voices[voice_index].sinewave->setType((int)PARAM(index));
    }
    return true;
  }
  else {
    return false;
  }
}

void KickMakerCore::setVoice(int index) {
  switch(index) {
    case PRM_1_ENABLED:
      if(PARAM(PRM_1_ENABLED) > 0.5) {
        m_voices[0].enabled = true;
      }
      else {
        m_voices[0].enabled = false;
      }
      break;
    case PRM_1_PHASE:
      m_voices[0].phase = PARAM(PRM_1_PHASE);
      break;
    case PRM_1_VOLUME:
      m_voices[0].volume = PARAM(PRM_1_VOLUME);
      break;
    case PRM_1_ATTACK:
    case PRM_1_ATTACK_AMP:
    case PRM_1_DECAY:
    case PRM_1_DECAY_AMP:
    case PRM_1_SUSTAIN:
    case PRM_1_SUSTAIN_AMP:
    case PRM_1_RELEASE:
      m_voices[0].adsr->recache();
      break;
      
    case PRM_2_ENABLED:
      if(PARAM(PRM_2_ENABLED) > 0.5) {
        m_voices[1].enabled = true;
      }
      else {
        m_voices[1].enabled = false;
      }
      break;
    case PRM_2_PHASE:
      m_voices[1].phase = PARAM(PRM_2_PHASE);
      break;
    case PRM_2_VOLUME:
      m_voices[1].volume = PARAM(PRM_2_VOLUME);
      break;
    case PRM_2_ATTACK:
    case PRM_2_ATTACK_AMP:
    case PRM_2_DECAY:
    case PRM_2_DECAY_AMP:
    case PRM_2_SUSTAIN:
    case PRM_2_SUSTAIN_AMP:
    case PRM_2_RELEASE:
      m_voices[1].adsr->recache();
      break;
      
    case PRM_3_ENABLED:
      if(PARAM(PRM_3_ENABLED) > 0.5) {
        m_voices[2].enabled = true;
      }
      else {
        m_voices[2].enabled = false;
      }
      break;
    case PRM_3_PHASE:
      m_voices[2].phase = PARAM(PRM_3_PHASE);
      break;
    case PRM_3_VOLUME:
      m_voices[2].volume = PARAM(PRM_3_VOLUME);
      break;
    case PRM_3_ATTACK:
    case PRM_3_ATTACK_AMP:
    case PRM_3_DECAY:
    case PRM_3_DECAY_AMP:
    case PRM_3_SUSTAIN:
    case PRM_3_SUSTAIN_AMP:
    case PRM_3_RELEASE:
      m_voices[2].adsr->recache();
      break;
      
    case PRM_4_ENABLED:
      if(PARAM(PRM_4_ENABLED) > 0.5) {
        m_voices[3].enabled = true;
      }
      else {
        m_voices[3].enabled = false;
      }
      break;
    case PRM_4_PHASE:
      m_voices[3].phase = PARAM(PRM_4_PHASE);
      break;
    case PRM_4_VOLUME:
      m_voices[3].volume = PARAM(PRM_4_VOLUME);
      break;
    case PRM_4_ATTACK:
    case PRM_4_ATTACK_AMP:
    case PRM_4_DECAY:
    case PRM_4_DECAY_AMP:
    case PRM_4_SUSTAIN:
    case PRM_4_SUSTAIN_AMP:
    case PRM_4_RELEASE:
      m_voices[3].adsr->recache();
      break;
      
    case PRM_ALL_ATTACK:
    case PRM_ALL_ATTACK_AMP:
    case PRM_ALL_DECAY:
    case PRM_ALL_DECAY_AMP:
    case PRM_ALL_SUSTAIN:
    case PRM_ALL_SUSTAIN_AMP:
    case PRM_ALL_RELEASE:
      m_adsr->recache();
      break;
      
    default:
      break;
  }  
}
