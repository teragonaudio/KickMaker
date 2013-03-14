/*
*  KickMaker - KickMakerEditor.cpp
*  Created by Nik Reiman on 03.02.06
*  Copyright (c) 2006 Teragon Audio, All rights reserved
*/

#ifndef __KickMakerEditor_H
#include "KickMakerEditor.h"
#endif

#ifndef __defaults_H
#include "defaults.h"
#endif

#ifndef __vstcontrols__
#include "vstcontrols.h"
#endif

// VSTGUI Stuff //////////////////////////////////////////////////////////
#if PLUGGUI
KickMakerEditor::KickMakerEditor(void *effect) : AEffGUIEditor(effect) {
#else
KickMakerEditor::KickMakerEditor(AudioEffect *effect) : AEffGUIEditor(effect) {
#endif
  m_opened = false;
  m_window = 0;
  
  m_background = new CBitmap(REZ_BACKGROUND);
  rect.left = 0;
  rect.top = 0;
  rect.right = (short)m_background->getWidth();
  rect.bottom = (short)m_background->getHeight();
  
  setKnobMode(kLinearMode);
  core = 0;
  
  m_preset_edit = 0;
  m_next_button = 0;
  m_prev_button = 0;
  m_save_button = 0;
  m_delete_button = 0;
  
  m_effect_label1_1 = 0;
  m_effect_meter1_1 = 0;
  m_effect_meter_vu1_1 = 0;
  m_effect_label1_2 = 0;
  m_effect_meter1_2 = 0;
  m_effect_meter_vu1_2 = 0;
  m_effect_label1_3 = 0;
  m_effect_meter1_3 = 0;
  m_effect_meter_vu1_3 = 0;
  m_freq1 = 0;
  m_freq_fine1 = 0;
  m_attack1 = 0;
  m_attack_amp1 = 0;
  m_decay1 = 0;
  m_decay_amp1 = 0;
  m_sustain1 = 0;
  m_sustain_amp1 = 0;
  m_release1 = 0;
  m_enabled1 = 0;
  m_switch1 = 0;
  m_adsr1 = 0;
  
  m_effect_label2_1 = 0;
  m_effect_meter2_1 = 0;
  m_effect_meter_vu2_1 = 0;
  m_effect_label2_2 = 0;
  m_effect_meter2_2 = 0;
  m_effect_meter_vu2_2 = 0;
  m_effect_label2_3 = 0;
  m_effect_meter2_3 = 0;
  m_effect_meter_vu2_3 = 0;
  m_freq2 = 0;
  m_freq_fine2 = 0;
  m_attack2 = 0;
  m_attack_amp2 = 0;
  m_decay2 = 0;
  m_decay_amp2 = 0;
  m_sustain2 = 0;
  m_sustain_amp2 = 0;
  m_release2 = 0;
  m_enabled2 = 0;
  m_switch2 = 0;
  m_adsr2 = 0;
  
  m_volume1 = 0;
  m_volume2 = 0;
  m_volume3 = 0;
  m_volume4 = 0;
  
  m_attack = 0;
  m_attack_amp = 0;
  m_decay = 0;
  m_decay_amp = 0;
  m_sustain = 0;
  m_sustain_amp = 0;
  m_release = 0;
  m_adsr = 0;
  m_volume = 0;
  
  for(int i = 0; i < sizeof(coords) / sizeof(struct tCoords); ++i) {
    m_coordmap.push_back(coords[i]);
  }
}

KickMakerEditor::~KickMakerEditor() {
  if(m_background) {
    m_background->forget();
  }
  m_background = 0;
}

void KickMakerEditor::close() {
  m_opened = false;
  delete frame;
  frame = 0;
}

void KickMakerEditor::addMenuOptions(cKeyedOptionMenu *menu) {
  menu->addKey("Phase 1", PRM_1_PHASE);
  menu->addKey("Phase 2", PRM_2_PHASE);
  menu->addKey("Phase 3", PRM_3_PHASE);
  menu->addKey("Phase 4", PRM_4_PHASE);
  menu->addKey("Noise 1", PRM_1_NOISE);
  menu->addKey("Noise 2", PRM_2_NOISE);
  menu->addKey("Noise 3", PRM_3_NOISE);
  menu->addKey("Noise 4", PRM_4_NOISE);
  menu->addKey("Freq. Expand 1", PRM_1_FREQ_EXPAND);
  menu->addKey("Freq. Expand 2", PRM_2_FREQ_EXPAND);
  menu->addKey("Freq. Expand 3", PRM_3_FREQ_EXPAND);
  menu->addKey("Freq. Expand 4", PRM_4_FREQ_EXPAND);
  menu->addKey("Freq. Rate 1", PRM_1_FREQ_EXPAND_RATE);
  menu->addKey("Freq. Rate 2", PRM_2_FREQ_EXPAND_RATE);
  menu->addKey("Freq. Rate 3", PRM_3_FREQ_EXPAND_RATE);
  menu->addKey("Freq. Rate 4", PRM_4_FREQ_EXPAND_RATE);
  menu->addKey("Comp. Attack", PRM_COMP_ATTACK);
  menu->addKey("Comp. Release", PRM_COMP_RELEASE);
  menu->addKey("Comp. Ratio", PRM_COMP_RATIO);
  menu->addKey("Comp. Thresh", PRM_COMP_THRESH);
  menu->addKey("Filter Freq", PRM_LOPASS_FREQ);
  menu->addKey("Filter Resonance", PRM_LOPASS_RESONANCE);
  menu->addKey("Wave Type 1", PRM_1_WAVE_TYPE);
  menu->addKey("Wave Type 2", PRM_2_WAVE_TYPE);
  menu->addKey("Wave Type 3", PRM_3_WAVE_TYPE);
  menu->addKey("Wave Type 4", PRM_4_WAVE_TYPE);
#if FEATURE_LFO
  menu->addKey("LFO 1 Enable", PRM_LFO_1_ENABLE);
  menu->addKey("LFO 1 Rate", PRM_LFO_1_RATE);
  menu->addKey("LFO 1 Amount", PRM_LFO_1_AMOUNT);
  menu->addKey("LFO 1 Target", PRM_LFO_1_TARGET);
  menu->addKey("LFO 2 Enable", PRM_LFO_2_ENABLE);
  menu->addKey("LFO 2 Rate", PRM_LFO_2_RATE);
  menu->addKey("LFO 2 Amount", PRM_LFO_2_AMOUNT);
  menu->addKey("LFO 2 Target", PRM_LFO_2_TARGET);
  menu->addKey("LFO 3 Enable", PRM_LFO_3_ENABLE);
  menu->addKey("LFO 3 Rate", PRM_LFO_3_RATE);
  menu->addKey("LFO 3 Amount", PRM_LFO_3_AMOUNT);
#endif
}

void* KickMakerEditor::getWindow() const {
  return m_window;
}

void KickMakerEditor::idle() {
  AEffGUIEditor::idle();
  m_events.update(getTicks());
}

#if USE_PC_AU
void KickMakerEditor::setAU(AudioUnit unit) {
  au = unit;
}
#endif

bool KickMakerEditor::setCoords(int tag, CRect &size, int width, int height) const {
  for(unsigned int i = 0; i < m_coordmap.size(); ++i) {
    if(m_coordmap.at(i).tag == tag) {
      size(m_coordmap.at(i).x, m_coordmap.at(i).y, m_coordmap.at(i).x + width,
           m_coordmap.at(i).y + height);
      return true;
    }
  }
  return false;
}

void KickMakerEditor::setCore(pluginCore *p) {
  if(!core && p) {
    core = p;
  }
  else {
    core = NULL;
  }
}

#if USE_PC_VST
void KickMakerEditor::beginEdit(VstInt32 index) {
  ((AudioEffectX*)effect)->beginEdit(index);
}

void KickMakerEditor::endEdit(VstInt32 index) {
  ((AudioEffectX*)effect)->endEdit(index);
}
#endif

void KickMakerEditor::fillPresetMenu(cOptionMenuHidden *menu) {
  char buf[MAX_MENU_NAME], pbuf[MAX_MENU_NAME];
  int i;
  for(i = 0; i < core->getNumPresets(); ++i) {
    core->getPresetName(i, (char*)&buf);
    core->getPresetBank(i, (char*)&pbuf);
    if(pbuf[0] != '\0') {
      if(menu->findSubmenu(pbuf) < 0) {
        menu->addSubmenu(pbuf);
      }
      (menu->getSubMenu(menu->findSubmenu(pbuf)))->addEntry(buf);
    }
    else {
      menu->addEntry(buf);
    }
  }
  // m_logger->logD(1014, i);
}

#if PLUGGUI
void KickMakerEditor::setParameter(long index, float value) {
#else
void KickMakerEditor::setParameter(VstInt32 index, float value) {
#endif
  if(!m_opened) {
    return;
  }
  
#if USE_PC_AU
  core->setParameterNormalized(index, value);
  AudioUnitParameter param;
  param.mAudioUnit = au;
  param.mParameterID = index;
  param.mScope = kAudioUnitScope_Global;
  param.mElement = 0;
  AUParameterListenerNotify(NULL, NULL, &param);
#elif USE_PC_VST
  effect->setParameterAutomated(index, value);
#endif
}

void KickMakerEditor::switch1() {
  if(m_sw_switch1 == 0) {
    m_sw_enabled1 = PRM_1_ENABLED;
    m_sw_freq1 = PRM_1_FREQ;
    m_sw_freq_fine1 = PRM_1_FREQ_FINE;
    m_sw_attack1 = PRM_1_ATTACK;
    m_sw_decay1 = PRM_1_DECAY;
    m_sw_sustain1 = PRM_1_SUSTAIN;
    m_sw_release1 = PRM_1_RELEASE;
    m_sw_attack_amp1 = PRM_1_ATTACK_AMP;
    m_sw_decay_amp1 = PRM_1_DECAY_AMP;
    m_sw_sustain_amp1 = PRM_1_SUSTAIN_AMP;
  }
  else {
    m_sw_enabled1 = PRM_2_ENABLED;
    m_sw_freq1 = PRM_2_FREQ;
    m_sw_freq_fine1 = PRM_2_FREQ_FINE;
    m_sw_attack1 = PRM_2_ATTACK;
    m_sw_decay1 = PRM_2_DECAY;
    m_sw_sustain1 = PRM_2_SUSTAIN;
    m_sw_release1 = PRM_2_RELEASE;
    m_sw_attack_amp1 = PRM_2_ATTACK_AMP;
    m_sw_decay_amp1 = PRM_2_DECAY_AMP;
    m_sw_sustain_amp1 = PRM_2_SUSTAIN_AMP;
  }
  
  m_effect1_1 = m_effect_label1_1->getCurrentKey();
  m_effect1_2 = m_effect_label1_2->getCurrentKey();
  m_effect1_3 = m_effect_label1_3->getCurrentKey();

  if(m_enabled1) {
    m_enabled1->setTag(m_sw_enabled1);
  }
  if(m_freq1) {
    m_freq1->setTag(m_sw_freq1);
  }
  if(m_freq_fine1) {
    m_freq_fine1->setTag(m_sw_freq_fine1);
  }
  if(m_attack1) {
    m_attack1->setTag(m_sw_attack1);
  }
  if(m_decay1) {
    m_decay1->setTag(m_sw_decay1);
  }
  if(m_sustain1) {
    m_sustain1->setTag(m_sw_sustain1);
  }
  if(m_release1) {
    m_release1->setTag(m_sw_release1);
  }
  if(m_attack_amp1) {
    m_attack_amp1->setTag(m_sw_attack_amp1);
  }
  if(m_decay_amp1) {
    m_decay_amp1->setTag(m_sw_decay_amp1);
  }
  if(m_sustain_amp1) {
    m_sustain_amp1->setTag(m_sw_sustain_amp1);
  }
}

void KickMakerEditor::switch2() {
  if(m_sw_switch2 == 0) {
    m_sw_enabled2 = PRM_3_ENABLED;
    m_sw_freq2 = PRM_3_FREQ;
    m_sw_freq_fine2 = PRM_3_FREQ_FINE;
    m_sw_attack2 = PRM_3_ATTACK;
    m_sw_decay2 = PRM_3_DECAY;
    m_sw_sustain2 = PRM_3_SUSTAIN;
    m_sw_release2 = PRM_3_RELEASE;
    m_sw_attack_amp2 = PRM_3_ATTACK_AMP;
    m_sw_decay_amp2 = PRM_3_DECAY_AMP;
    m_sw_sustain_amp2 = PRM_3_SUSTAIN_AMP;
  }
  else {
    m_sw_enabled2 = PRM_4_ENABLED;
    m_sw_freq2 = PRM_4_FREQ;
    m_sw_freq_fine2 = PRM_4_FREQ_FINE;
    m_sw_attack2 = PRM_4_ATTACK;
    m_sw_decay2 = PRM_4_DECAY;
    m_sw_sustain2 = PRM_4_SUSTAIN;
    m_sw_release2 = PRM_4_RELEASE;
    m_sw_attack_amp2 = PRM_4_ATTACK_AMP;
    m_sw_decay_amp2 = PRM_4_DECAY_AMP;
    m_sw_sustain_amp2 = PRM_4_SUSTAIN_AMP;
  }

  m_effect2_1 = m_effect_label2_1->getCurrentKey();
  m_effect2_2 = m_effect_label2_2->getCurrentKey();
  m_effect2_3 = m_effect_label2_3->getCurrentKey();

  if(m_enabled2) {
    m_enabled2->setTag(m_sw_enabled2);
  }
  if(m_freq2) {
    m_freq2->setTag(m_sw_freq2);
  }
  if(m_freq_fine2) {
    m_freq_fine2->setTag(m_sw_freq_fine2);
  }
  if(m_attack2) {
    m_attack2->setTag(m_sw_attack2);
  }
  if(m_decay2) {
    m_decay2->setTag(m_sw_decay2);
  }
  if(m_sustain2) {
    m_sustain2->setTag(m_sw_sustain2);
  }
  if(m_release2) {
    m_release2->setTag(m_sw_release2);
  }
  if(m_attack_amp2) {
    m_attack_amp2->setTag(m_sw_attack_amp2);
  }
  if(m_decay_amp2) {
    m_decay_amp2->setTag(m_sw_decay_amp2);
  }
  if(m_sustain_amp2) {
    m_sustain_amp2->setTag(m_sw_sustain_amp2);
  }
}

void KickMakerEditor::updateControl(int tag) {
  if(!m_opened) {
    return;
  }
  
  if(tag == m_sw_attack1) {
    m_attack1->setValue(core->getParameterScaled(m_sw_attack1));
    m_adsr1->setAttackCoords(core->getParameter(REQ_VALUE_RAW, m_sw_attack1, NULL),
                             core->getParameter(REQ_VALUE_RAW, m_sw_attack_amp1, NULL));
    m_adsr1->setDecayCoords(core->getParameter(REQ_VALUE_RAW, m_sw_decay1, NULL),
                            core->getParameter(REQ_VALUE_RAW, m_sw_decay_amp1, NULL));
    m_adsr1->setSustainCoords(core->getParameter(REQ_VALUE_RAW, m_sw_sustain1, NULL),
                              core->getParameter(REQ_VALUE_RAW, m_sw_sustain_amp1, NULL));
    m_adsr1->setReleaseCoords(core->getParameter(REQ_VALUE_RAW, m_sw_release1, NULL), 0.0);
  }
  else if(tag == m_sw_decay1) {
    m_decay1->setValue(core->getParameterScaled(m_sw_decay1));
    m_adsr1->setDecayCoords(core->getParameter(REQ_VALUE_RAW, m_sw_decay1, NULL),
                            core->getParameter(REQ_VALUE_RAW, m_sw_decay_amp1, NULL));
    m_adsr1->setSustainCoords(core->getParameter(REQ_VALUE_RAW, m_sw_sustain1, NULL),
                              core->getParameter(REQ_VALUE_RAW, m_sw_sustain_amp1, NULL));
    m_adsr1->setReleaseCoords(core->getParameter(REQ_VALUE_RAW, m_sw_release1, NULL), 0.0);
  }
  else if(tag == m_sw_sustain1) {
    m_sustain1->setValue(core->getParameterScaled(m_sw_sustain1));
    m_adsr1->setSustainCoords(core->getParameter(REQ_VALUE_RAW, m_sw_sustain1, NULL),
                              core->getParameter(REQ_VALUE_RAW, m_sw_sustain_amp1, NULL));
    m_adsr1->setReleaseCoords(core->getParameter(REQ_VALUE_RAW, m_sw_release1, NULL), 0.0);
  }
  else if(tag == m_sw_release1) {
    m_release1->setValue(core->getParameterScaled(m_sw_release1));
    m_adsr1->setReleaseCoords(core->getParameter(REQ_VALUE_RAW, m_sw_release1, NULL), 0.0);
  }
  else if(tag == m_sw_attack_amp1) {
    m_attack_amp1->setValue(core->getParameterScaled(m_sw_attack_amp1));
    m_adsr1->setAttackCoords(core->getParameter(REQ_VALUE_RAW, m_sw_attack1, NULL),
                             core->getParameter(REQ_VALUE_RAW, m_sw_attack_amp1, NULL));
    m_adsr1->setDecayCoords(core->getParameter(REQ_VALUE_RAW, m_sw_decay1, NULL),
                            core->getParameter(REQ_VALUE_RAW, m_sw_decay_amp1, NULL));
    m_adsr1->setSustainCoords(core->getParameter(REQ_VALUE_RAW, m_sw_sustain1, NULL),
                              core->getParameter(REQ_VALUE_RAW, m_sw_sustain_amp1, NULL));
    m_adsr1->setReleaseCoords(core->getParameter(REQ_VALUE_RAW, m_sw_release1, NULL), 0.0);
  }
  else if(tag == m_sw_decay_amp1) {
    m_decay_amp1->setValue(core->getParameterScaled(m_sw_decay_amp1));
    m_adsr1->setDecayCoords(core->getParameter(REQ_VALUE_RAW, m_sw_decay1, NULL),
                            core->getParameter(REQ_VALUE_RAW, m_sw_decay_amp1, NULL));
    m_adsr1->setSustainCoords(core->getParameter(REQ_VALUE_RAW, m_sw_sustain1, NULL),
                              core->getParameter(REQ_VALUE_RAW, m_sw_sustain_amp1, NULL));
    m_adsr1->setReleaseCoords(core->getParameter(REQ_VALUE_RAW, m_sw_release1, NULL), 0.0);
  }
  else if(tag == m_sw_sustain_amp1) {
    m_sustain_amp1->setValue(core->getParameterScaled(m_sw_sustain_amp1));
    m_adsr1->setSustainCoords(core->getParameter(REQ_VALUE_RAW, m_sw_sustain1, NULL),
                              core->getParameter(REQ_VALUE_RAW, m_sw_sustain_amp1, NULL));
    m_adsr1->setReleaseCoords(core->getParameter(REQ_VALUE_RAW, m_sw_release1, NULL), 0.0);
  }
  else if(tag == m_sw_freq1) {
    m_freq1->setValue(core->getParameterScaled(m_sw_freq1));
  }
  else if(tag == m_sw_enabled1) {
    m_enabled1->setValue(core->getParameterScaled(m_sw_enabled1));
  }

  if(tag == m_sw_attack2) {
    m_attack2->setValue(core->getParameterScaled(m_sw_attack2));
    m_adsr2->setAttackCoords(core->getParameter(REQ_VALUE_RAW, m_sw_attack2, NULL),
                             core->getParameter(REQ_VALUE_RAW, m_sw_attack_amp2, NULL));
    m_adsr2->setDecayCoords(core->getParameter(REQ_VALUE_RAW, m_sw_decay2, NULL),
                            core->getParameter(REQ_VALUE_RAW, m_sw_decay_amp2, NULL));
    m_adsr2->setSustainCoords(core->getParameter(REQ_VALUE_RAW, m_sw_sustain2, NULL),
                              core->getParameter(REQ_VALUE_RAW, m_sw_sustain_amp2, NULL));
    m_adsr2->setReleaseCoords(core->getParameter(REQ_VALUE_RAW, m_sw_release2, NULL), 0.0);
  }
  else if(tag == m_sw_decay2) {
    m_decay2->setValue(core->getParameterScaled(m_sw_decay2));
    m_adsr2->setDecayCoords(core->getParameter(REQ_VALUE_RAW, m_sw_decay2, NULL),
                            core->getParameter(REQ_VALUE_RAW, m_sw_decay_amp2, NULL));
    m_adsr2->setSustainCoords(core->getParameter(REQ_VALUE_RAW, m_sw_sustain2, NULL),
                              core->getParameter(REQ_VALUE_RAW, m_sw_sustain_amp2, NULL));
    m_adsr2->setReleaseCoords(core->getParameter(REQ_VALUE_RAW, m_sw_release2, NULL), 0.0);
  }
  else if(tag == m_sw_sustain2) {
    m_sustain2->setValue(core->getParameterScaled(m_sw_sustain2));
    m_adsr2->setSustainCoords(core->getParameter(REQ_VALUE_RAW, m_sw_sustain2, NULL),
                              core->getParameter(REQ_VALUE_RAW, m_sw_sustain_amp2, NULL));
    m_adsr2->setReleaseCoords(core->getParameter(REQ_VALUE_RAW, m_sw_release2, NULL), 0.0);
  }
  else if(tag == m_sw_release2) {
    m_release2->setValue(core->getParameterScaled(m_sw_release2));
    m_adsr2->setReleaseCoords(core->getParameter(REQ_VALUE_RAW, m_sw_release2, NULL), 0.0);
  }
  else if(tag == m_sw_attack_amp2) {
    m_attack_amp2->setValue(core->getParameterScaled(m_sw_attack_amp2));
    m_adsr2->setAttackCoords(core->getParameter(REQ_VALUE_RAW, m_sw_attack2, NULL),
                             core->getParameter(REQ_VALUE_RAW, m_sw_attack_amp2, NULL));
    m_adsr2->setDecayCoords(core->getParameter(REQ_VALUE_RAW, m_sw_decay2, NULL),
                            core->getParameter(REQ_VALUE_RAW, m_sw_decay_amp2, NULL));
    m_adsr2->setSustainCoords(core->getParameter(REQ_VALUE_RAW, m_sw_sustain2, NULL),
                              core->getParameter(REQ_VALUE_RAW, m_sw_sustain_amp2, NULL));
  }
  else if(tag == m_sw_decay_amp2) {
    m_decay_amp2->setValue(core->getParameterScaled(m_sw_decay_amp2));
    m_adsr2->setDecayCoords(core->getParameter(REQ_VALUE_RAW, m_sw_decay2, NULL),
                            core->getParameter(REQ_VALUE_RAW, m_sw_decay_amp2, NULL));
    m_adsr2->setSustainCoords(core->getParameter(REQ_VALUE_RAW, m_sw_sustain2, NULL),
                              core->getParameter(REQ_VALUE_RAW, m_sw_sustain_amp2, NULL));
  }
  else if(tag == m_sw_sustain_amp2) {
    m_sustain_amp2->setValue(core->getParameterScaled(m_sw_sustain_amp2));
    m_adsr2->setSustainCoords(core->getParameter(REQ_VALUE_RAW, m_sw_sustain2, NULL),
                              core->getParameter(REQ_VALUE_RAW, m_sw_sustain_amp2, NULL));
  }
  else if(tag == m_sw_freq2) {
    m_freq2->setValue(core->getParameterScaled(m_sw_freq2));
  }
  else if(tag == m_sw_enabled2) {
    m_enabled2->setValue(core->getParameterScaled(m_sw_enabled2));
  }
  
  else if(tag == PRM_ALL_ATTACK) {
    m_attack->setValue(core->getParameterScaled(PRM_ALL_ATTACK));
    m_adsr->setAttackCoords(core->getParameter(REQ_VALUE_RAW, PRM_ALL_ATTACK, NULL),
                            core->getParameter(REQ_VALUE_RAW, PRM_ALL_ATTACK_AMP, NULL));
    m_adsr->setDecayCoords(core->getParameter(REQ_VALUE_RAW, PRM_ALL_DECAY, NULL),
                           core->getParameter(REQ_VALUE_RAW, PRM_ALL_DECAY_AMP, NULL));
    m_adsr->setSustainCoords(core->getParameter(REQ_VALUE_RAW, PRM_ALL_SUSTAIN, NULL),
                             core->getParameter(REQ_VALUE_RAW, PRM_ALL_SUSTAIN_AMP, NULL));
    m_adsr->setReleaseCoords(core->getParameter(REQ_VALUE_RAW, PRM_ALL_RELEASE, NULL), 0.0);
  }
  else if(tag == PRM_ALL_DECAY) {
    m_decay->setValue(core->getParameterScaled(PRM_ALL_DECAY));
    m_adsr->setDecayCoords(core->getParameter(REQ_VALUE_RAW, PRM_ALL_DECAY, NULL),
                           core->getParameter(REQ_VALUE_RAW, PRM_ALL_DECAY_AMP, NULL));
    m_adsr->setSustainCoords(core->getParameter(REQ_VALUE_RAW, PRM_ALL_SUSTAIN, NULL),
                             core->getParameter(REQ_VALUE_RAW, PRM_ALL_SUSTAIN_AMP, NULL));
    m_adsr->setReleaseCoords(core->getParameter(REQ_VALUE_RAW, PRM_ALL_RELEASE, NULL), 0.0);
  }
  else if(tag == PRM_ALL_SUSTAIN) {
    m_sustain->setValue(core->getParameterScaled(PRM_ALL_SUSTAIN));
    m_adsr->setSustainCoords(core->getParameter(REQ_VALUE_RAW, PRM_ALL_SUSTAIN, NULL),
                             core->getParameter(REQ_VALUE_RAW, PRM_ALL_SUSTAIN_AMP, NULL));
    m_adsr->setReleaseCoords(core->getParameter(REQ_VALUE_RAW, PRM_ALL_RELEASE, NULL), 0.0);
  }
  else if(tag == PRM_ALL_RELEASE) {
    m_release->setValue(core->getParameterScaled(PRM_ALL_RELEASE));
    m_adsr->setReleaseCoords(core->getParameter(REQ_VALUE_RAW, PRM_ALL_RELEASE, NULL), 0.0);
  }
  else if(tag == PRM_ALL_ATTACK_AMP) {
    m_attack_amp->setValue(core->getParameterScaled(PRM_ALL_ATTACK_AMP));
    m_adsr->setAttackCoords(core->getParameter(REQ_VALUE_RAW, PRM_ALL_ATTACK, NULL),
                            core->getParameter(REQ_VALUE_RAW, PRM_ALL_ATTACK_AMP, NULL));
    m_adsr->setDecayCoords(core->getParameter(REQ_VALUE_RAW, PRM_ALL_DECAY, NULL),
                           core->getParameter(REQ_VALUE_RAW, PRM_ALL_DECAY_AMP, NULL));
    m_adsr->setSustainCoords(core->getParameter(REQ_VALUE_RAW, PRM_ALL_SUSTAIN, NULL),
                             core->getParameter(REQ_VALUE_RAW, PRM_ALL_SUSTAIN_AMP, NULL));
  }
  else if(tag == PRM_ALL_DECAY_AMP) {
    m_decay_amp->setValue(core->getParameterScaled(PRM_ALL_DECAY_AMP));
    m_adsr->setDecayCoords(core->getParameter(REQ_VALUE_RAW, PRM_ALL_DECAY, NULL),
                           core->getParameter(REQ_VALUE_RAW, PRM_ALL_DECAY_AMP, NULL));
    m_adsr->setSustainCoords(core->getParameter(REQ_VALUE_RAW, PRM_ALL_SUSTAIN, NULL),
                             core->getParameter(REQ_VALUE_RAW, PRM_ALL_SUSTAIN_AMP, NULL));
  }
  else if(tag == PRM_ALL_SUSTAIN_AMP) {
    m_sustain_amp->setValue(core->getParameterScaled(PRM_ALL_SUSTAIN_AMP));
    m_adsr->setSustainCoords(core->getParameter(REQ_VALUE_RAW, PRM_ALL_SUSTAIN, NULL),
                             core->getParameter(REQ_VALUE_RAW, PRM_ALL_SUSTAIN_AMP, NULL));
  }
  
  else if(tag == PRM_1_VOLUME) {
    m_volume1->setValue(core->getParameterScaled(PRM_1_VOLUME));
  }
  else if(tag == PRM_2_VOLUME) {
    m_volume2->setValue(core->getParameterScaled(PRM_2_VOLUME));
  }
  else if(tag == PRM_3_VOLUME) {
    m_volume3->setValue(core->getParameterScaled(PRM_3_VOLUME));
  }
  else if(tag == PRM_4_VOLUME) {
    m_volume4->setValue(core->getParameterScaled(PRM_4_VOLUME));
  }
  else if(tag == PRM_ALL_VOLUME) {
    m_volume->setValue(core->getParameterScaled(PRM_ALL_VOLUME));
  }
}

void KickMakerEditor::updateDisplay() {
  if(!m_opened) {
    return;
  }
  
  // m_logger->logS(1015);
  m_effect_meter_vu1_1->setValue(core->getParameterScaled(m_effect_label1_1->getCurrentKey()));
  m_effect_meter1_1->setValue(core->getParameterScaled(m_effect_label1_1->getCurrentKey()));
  m_effect_meter_vu1_2->setValue(core->getParameterScaled(m_effect_label1_2->getCurrentKey()));
  m_effect_meter1_2->setValue(core->getParameterScaled(m_effect_label1_2->getCurrentKey()));
  m_effect_meter_vu1_3->setValue(core->getParameterScaled(m_effect_label1_3->getCurrentKey()));
  m_effect_meter1_3->setValue(core->getParameterScaled(m_effect_label1_3->getCurrentKey()));

  m_effect_meter_vu1_1->setDirty();
  m_effect_meter1_1->setDirty();
  m_effect_meter_vu1_2->setDirty();
  m_effect_meter1_2->setDirty();
  m_effect_meter_vu1_3->setDirty();
  m_effect_meter1_3->setDirty();
  
  m_enabled1->setValue(core->getParameterScaled(m_sw_enabled1));
  m_freq1->setValue(core->getParameterScaled(m_sw_freq1));
  m_freq_fine1->setValue(0.5);
  
  m_attack1->setValue(core->getParameterScaled(m_sw_attack1));
  m_attack_amp1->setValue(core->getParameterScaled(m_sw_attack_amp1));
  m_decay1->setValue(core->getParameterScaled(m_sw_decay1));
  m_decay_amp1->setValue(core->getParameterScaled(m_sw_decay_amp1));
  m_sustain1->setValue(core->getParameterScaled(m_sw_sustain1));
  m_sustain_amp1->setValue(core->getParameterScaled(m_sw_sustain_amp1));
  m_release1->setValue(core->getParameterScaled(m_sw_release1));
  
  m_adsr1->setAttackCoords(core->getParameter(REQ_VALUE_RAW, m_sw_attack1, NULL),
                           core->getParameter(REQ_VALUE_RAW, m_sw_attack_amp1, NULL));
  m_adsr1->setDecayCoords(core->getParameter(REQ_VALUE_RAW, m_sw_decay1, NULL),
                          core->getParameter(REQ_VALUE_RAW, m_sw_decay_amp1, NULL));
  m_adsr1->setSustainCoords(core->getParameter(REQ_VALUE_RAW, m_sw_sustain1, NULL),
                            core->getParameter(REQ_VALUE_RAW, m_sw_sustain_amp1, NULL));
  m_adsr1->setReleaseCoords(core->getParameter(REQ_VALUE_RAW, m_sw_release1, NULL), 0.0);
  
  m_effect_meter_vu2_1->setValue(core->getParameterScaled(m_effect_label2_1->getCurrentKey()));
  m_effect_meter2_1->setValue(core->getParameterScaled(m_effect_label2_1->getCurrentKey()));
  m_effect_meter_vu2_2->setValue(core->getParameterScaled(m_effect_label2_2->getCurrentKey()));
  m_effect_meter2_2->setValue(core->getParameterScaled(m_effect_label2_2->getCurrentKey()));
  m_effect_meter_vu2_3->setValue(core->getParameterScaled(m_effect_label2_3->getCurrentKey()));
  m_effect_meter2_3->setValue(core->getParameterScaled(m_effect_label2_3->getCurrentKey()));

  m_effect_meter_vu2_1->setDirty();
  m_effect_meter2_1->setDirty();
  m_effect_meter_vu2_2->setDirty();
  m_effect_meter2_2->setDirty();
  m_effect_meter_vu2_3->setDirty();
  m_effect_meter2_3->setDirty();
  
  m_enabled2->setValue(core->getParameterScaled(m_sw_enabled2));
  m_freq2->setValue(core->getParameterScaled(m_sw_freq2));
  m_freq_fine2->setValue(0.5);
  
  m_attack2->setValue(core->getParameterScaled(m_sw_attack2));
  m_attack_amp2->setValue(core->getParameterScaled(m_sw_attack_amp2));
  m_decay2->setValue(core->getParameterScaled(m_sw_decay2));
  m_decay_amp2->setValue(core->getParameterScaled(m_sw_decay_amp2));
  m_sustain2->setValue(core->getParameterScaled(m_sw_sustain2));
  m_sustain_amp2->setValue(core->getParameterScaled(m_sw_sustain_amp2));
  m_release2->setValue(core->getParameterScaled(m_sw_release2));
  
  m_adsr2->setAttackCoords(core->getParameter(REQ_VALUE_RAW, m_sw_attack2, NULL),
                           core->getParameter(REQ_VALUE_RAW, m_sw_attack_amp2, NULL));
  m_adsr2->setDecayCoords(core->getParameter(REQ_VALUE_RAW, m_sw_decay2, NULL),
                          core->getParameter(REQ_VALUE_RAW, m_sw_decay_amp2, NULL));
  m_adsr2->setSustainCoords(core->getParameter(REQ_VALUE_RAW, m_sw_sustain2, NULL),
                            core->getParameter(REQ_VALUE_RAW, m_sw_sustain_amp2, NULL));
  m_adsr2->setReleaseCoords(core->getParameter(REQ_VALUE_RAW, m_sw_release2, NULL), 0.0);
  
  m_attack_amp->setValue(core->getParameter(REQ_VALUE, PRM_ALL_ATTACK_AMP, NULL));
  m_decay_amp->setValue(core->getParameter(REQ_VALUE, PRM_ALL_DECAY_AMP, NULL));
  m_sustain_amp->setValue(core->getParameter(REQ_VALUE, PRM_ALL_SUSTAIN_AMP, NULL));
  m_attack->setValue(core->getParameterScaled(PRM_ALL_ATTACK));
  m_decay->setValue(core->getParameterScaled(PRM_ALL_DECAY));
  m_sustain->setValue(core->getParameterScaled(PRM_ALL_SUSTAIN));
  m_release->setValue(core->getParameterScaled(PRM_ALL_RELEASE));
  
  m_adsr->setAttackCoords(core->getParameter(REQ_VALUE_RAW, PRM_ALL_ATTACK, NULL),
                          core->getParameter(REQ_VALUE_RAW, PRM_ALL_ATTACK_AMP, NULL));
  m_adsr->setDecayCoords(core->getParameter(REQ_VALUE_RAW, PRM_ALL_DECAY, NULL),
                         core->getParameter(REQ_VALUE_RAW, PRM_ALL_DECAY_AMP, NULL));
  m_adsr->setSustainCoords(core->getParameter(REQ_VALUE_RAW, PRM_ALL_SUSTAIN, NULL),
                           core->getParameter(REQ_VALUE_RAW, PRM_ALL_SUSTAIN_AMP, NULL));
  m_adsr->setReleaseCoords(core->getParameter(REQ_VALUE_RAW, PRM_ALL_RELEASE, NULL), 0.0);
  
  m_volume1->setValue(core->getParameterScaled(PRM_1_VOLUME));
  m_volume2->setValue(core->getParameterScaled(PRM_2_VOLUME));
  m_volume3->setValue(core->getParameterScaled(PRM_3_VOLUME));
  m_volume4->setValue(core->getParameterScaled(PRM_4_VOLUME));
  m_volume->setValue(core->getParameterScaled(PRM_ALL_VOLUME));
}

void KickMakerEditor::menuOptionHandler(cLevelDisplayBitmap *level, int param)
{
  if(param >= PRM_1_WAVE_TYPE && param <= PRM_4_WAVE_TYPE)
  {
    level->setDisplayType(false);
    level->dictClear();
    for(int i = 0; i < WAV_LAST_WAV; ++i)
    {
      level->dictAddEntry(gDictionaryWaveTables[i]);
    }
  }
  else
  {
    level->setDisplayType(true);
  }
}

void KickMakerEditor::valueChanged(CDrawContext* pContext, CControl* pControl) {
  if(!m_opened) {
    return;
  }
  
  // m_logger->logF(1016, pControl->getTag(), pControl->getValue());
  setParameter(pControl->getTag(), pControl->getValue());
  
  char cbuf[32];
  bool lset = false;
  
  switch(pControl->getTag()) {
    case TAG_ABOUT_SPLASH:
      m_about->setVisible(true);
      break;
      
    case TAG_PRESET_MENU:
    {
      long mindex = -1;
      COptionMenu *ce = m_preset_menu->getLastItemMenu(mindex);
      if(ce) {
        ce->getCurrent(cbuf);
      }
      int pnum = core->findPreset(cbuf);
      core->loadPreset(pnum);
      core->getCurrentPresetName((char*)&cbuf);
      m_preset_label->setText(cbuf);
      updateDisplay();
    }
      break;
      
    // Oscillator switching
    case TAG_1_SWITCH:
      m_sw_switch1 = (int)pControl->getValue();
      switch1();
      updateDisplay();
      break;
    case TAG_2_SWITCH:
      m_sw_switch2 = (int)pControl->getValue();
      switch2();
      updateDisplay();
      break;

    case TAG_SAVE_BUTTON:
      if(pControl->getValue() && !m_preset_edit->getEnabled()) {
        m_preset_label->getText((char*)&cbuf);
        m_preset_label->setText(" ");
        m_preset_edit->setText(cbuf);
        m_preset_edit->setEnabled(true);
        CDrawContext *dc = new CDrawContext(frame, NULL, NULL);
        m_preset_edit->takeFocus(dc);
        delete dc;
      }
      break;
      
    // If this event is received, then the preset name has been edited, so the save is actually done HERE
    case TAG_PRESET_DISPLAY:
      // Escape was pressed
      if(!m_preset_edit->bWasReturnPressed) {
        core->getCurrentPresetName((char*)&cbuf);
        m_preset_label->setText(cbuf);
        m_preset_edit->setEnabled(false);
        break;
      }
      
      m_preset_edit->getText((char*)&cbuf);
      if(core->savePreset(DEF_PRODUCT, cbuf)) {
        core->loadPreset(core->getNumPresets() - 1);
        m_preset_menu->addEntry(cbuf);
      }
      m_preset_label->setText(cbuf);
      m_preset_edit->setEnabled(false);
      break;
      
    case TAG_NEXT_BUTTON:
      if(m_preset_edit->getEnabled()) {
        m_preset_edit->setEnabled(false);
      }
      
      if(pControl->getValue()) {
        core->nextPreset();
        core->getCurrentPresetName((char*)&cbuf);
        m_preset_label->setText(cbuf);
        updateDisplay();
      }
      break;
      
    case TAG_DELETE_BUTTON:
      if(m_preset_edit->getEnabled()) {
        m_preset_edit->setEnabled(false);
      }
      
      if(pControl->getValue()) {
        m_preset_label->getText((char*)&cbuf);
        core->deletePreset(cbuf);
        core->prevPreset();
        core->getCurrentPresetName((char*)&cbuf);
        m_preset_label->setText(cbuf);
        updateDisplay();
        break;
      }
      else {
        break;
      }

    case TAG_PREV_BUTTON:
      if(m_preset_edit->getEnabled()) {
        m_preset_edit->setEnabled(false);
      }
      
      if(pControl->getValue()) {
        core->prevPreset();
        core->getCurrentPresetName((char*)&cbuf);
        m_preset_label->setText(cbuf);
        updateDisplay();
      }
      break;
      
    // Check for effect changes
    case TAG_1_EFFECT_LABEL1:
      m_effect1_1 = m_effect_label1_1->getKey((int)pControl->getValue());
      menuOptionHandler(m_effect_meter_vu1_1, m_effect1_1);
      m_effect_meter_vu1_1->setValue(core->getParameterScaled(m_effect1_1));
      m_effect_meter_vu1_1->setDirty();
        
      m_effect_meter1_1->setValue(core->getParameterScaled(m_effect1_1));
      m_effect_meter1_1->setDirty();
      m_effect_knob1_1->setValue(core->getParameterScaled(m_effect1_1));
      break;
    case TAG_1_EFFECT_METER1:
      m_effect_meter_vu1_1->setValue(pControl->getValue());
      m_effect_knob1_1->setValue(pControl->getValue());
      core->setParameterNormalized(m_effect1_1, pControl->getValue());
      break;
    case TAG_1_EFFECT_KNOB1:
      m_effect_meter1_1->setValue(pControl->getValue());
      m_effect_meter_vu1_1->setValue(pControl->getValue());
      m_effect_meter1_1->setDirty();
      core->setParameterNormalized(m_effect1_1, pControl->getValue());
      break;
      
    case TAG_1_EFFECT_LABEL2:
      m_effect1_2 = m_effect_label1_2->getKey((int)pControl->getValue());
      menuOptionHandler(m_effect_meter_vu1_2, m_effect1_2);
      m_effect_meter_vu1_2->setValue(core->getParameterScaled(m_effect1_2));
      m_effect_meter_vu1_2->setDirty();
      
      m_effect_meter1_2->setValue(core->getParameterScaled(m_effect1_2));
      m_effect_meter1_2->setDirty();
      m_effect_knob1_2->setValue(core->getParameterScaled(m_effect1_2));
      break;
    case TAG_1_EFFECT_METER2:
      m_effect_meter_vu1_2->setValue(pControl->getValue());
      m_effect_knob1_2->setValue(pControl->getValue());
      core->setParameterNormalized(m_effect1_2, pControl->getValue());
      break;
    case TAG_1_EFFECT_KNOB2:
      m_effect_meter1_2->setValue(pControl->getValue());
      m_effect_meter_vu1_2->setValue(pControl->getValue());
      m_effect_meter1_2->setDirty();
      core->setParameterNormalized(m_effect1_2, pControl->getValue());
      break;
      
    case TAG_1_EFFECT_LABEL3:
      m_effect1_3 = m_effect_label1_3->getKey((int)pControl->getValue());
      menuOptionHandler(m_effect_meter_vu1_3, m_effect1_3);
      m_effect_meter_vu1_3->setValue(core->getParameterScaled(m_effect1_3));
      m_effect_meter_vu1_3->setDirty();
      
      m_effect_meter1_3->setValue(core->getParameterScaled(m_effect1_3));
      m_effect_meter1_3->setDirty();
      m_effect_knob1_3->setValue(core->getParameterScaled(m_effect1_3));
      break;
    case TAG_1_EFFECT_METER3:
      m_effect_meter_vu1_3->setValue(pControl->getValue());
      m_effect_knob1_3->setValue(pControl->getValue());
      core->setParameterNormalized(m_effect1_3, pControl->getValue());
      break;
    case TAG_1_EFFECT_KNOB3:
      m_effect_meter1_3->setValue(pControl->getValue());
      m_effect_meter_vu1_3->setValue(pControl->getValue());
      m_effect_meter1_3->setDirty();
      core->setParameterNormalized(m_effect1_3, pControl->getValue());
      break;
      
    case TAG_2_EFFECT_LABEL1:
      m_effect2_1 = m_effect_label2_1->getKey((int)pControl->getValue());
      menuOptionHandler(m_effect_meter_vu2_1, m_effect2_1);
      m_effect_meter_vu2_1->setValue(core->getParameterScaled(m_effect2_1));
      m_effect_meter_vu2_1->setDirty();
      
      m_effect_meter2_1->setValue(core->getParameterScaled(m_effect2_1));
      m_effect_meter2_1->setDirty();
      m_effect_knob2_1->setValue(core->getParameterScaled(m_effect2_1));
      break;
    case TAG_2_EFFECT_METER1:
      m_effect_meter_vu2_1->setValue(pControl->getValue());
      m_effect_knob2_1->setValue(pControl->getValue());
      core->setParameterNormalized(m_effect2_1, pControl->getValue());
      break;
    case TAG_2_EFFECT_KNOB1:
      m_effect_meter2_1->setValue(pControl->getValue());
      m_effect_meter_vu2_1->setValue(pControl->getValue());
      m_effect_meter2_1->setDirty();
      core->setParameterNormalized(m_effect2_1, pControl->getValue());
      break;
      
    case TAG_2_EFFECT_LABEL2:
      m_effect2_2 = m_effect_label2_2->getKey((int)pControl->getValue());
      menuOptionHandler(m_effect_meter_vu2_2, m_effect2_2);
      m_effect_meter_vu2_2->setValue(core->getParameterScaled(m_effect2_2));
      m_effect_meter_vu2_2->setDirty();
      
      m_effect_meter2_2->setValue(core->getParameterScaled(m_effect2_2));
      m_effect_meter2_2->setDirty();
      m_effect_knob2_2->setValue(core->getParameterScaled(m_effect2_2));
      break;
    case TAG_2_EFFECT_METER2:
      m_effect_meter_vu2_2->setValue(pControl->getValue());
      m_effect_knob2_2->setValue(pControl->getValue());
      core->setParameterNormalized(m_effect2_2, pControl->getValue());
      break;
    case TAG_2_EFFECT_KNOB2:
      m_effect_meter2_2->setValue(pControl->getValue());
      m_effect_meter_vu2_2->setValue(pControl->getValue());
      m_effect_meter2_2->setDirty();
      core->setParameterNormalized(m_effect2_2, pControl->getValue());
      break;
      
    case TAG_2_EFFECT_LABEL3:
      m_effect2_3 = m_effect_label2_3->getKey((int)pControl->getValue());
      menuOptionHandler(m_effect_meter_vu2_3, m_effect2_3);
      m_effect_meter_vu2_3->setValue(core->getParameterScaled(m_effect2_3));
      m_effect_meter_vu2_3->setDirty();
      
      m_effect_meter2_3->setValue(core->getParameterScaled(m_effect2_3));
      m_effect_meter2_3->setDirty();
      m_effect_knob2_3->setValue(core->getParameterScaled(m_effect2_3));
      break;
    case TAG_2_EFFECT_METER3:
      m_effect_meter_vu2_3->setValue(pControl->getValue());
      m_effect_knob2_3->setValue(pControl->getValue());
      core->setParameterNormalized(m_effect2_3, pControl->getValue());
      break;
    case TAG_2_EFFECT_KNOB3:
      m_effect_meter2_3->setValue(pControl->getValue());
      m_effect_meter_vu2_3->setValue(pControl->getValue());
      m_effect_meter2_3->setDirty();
      core->setParameterNormalized(m_effect2_3, pControl->getValue());
      break;
      
    // Reset the fine frequency tuners here
    case PRM_1_FREQ:
    case PRM_2_FREQ:
      m_freq1->setNumber(core->getParameter(REQ_VALUE_RAW, m_sw_freq1));
      m_events.addEvent(m_freq1, DEF_TICKS, 0);
      m_freq_fine1->setValue(0.5);
      break;
    case PRM_3_FREQ:
    case PRM_4_FREQ:
      m_freq2->setNumber(core->getParameter(REQ_VALUE_RAW, m_sw_freq2));
      m_events.addEvent(m_freq2, DEF_TICKS, 0);
      m_freq_fine2->setValue(0.5);
      break;
      
    case PRM_1_FREQ_FINE:
    case PRM_2_FREQ_FINE:
      m_freq_fine1->setNumber(core->getParameter(REQ_VALUE_RAW, m_sw_freq1) +
                              core->getParameter(REQ_VALUE_RAW, m_sw_freq_fine1));
      m_events.addEvent(m_freq_fine1, DEF_TICKS, 0);
      break;
    case PRM_3_FREQ_FINE:
    case PRM_4_FREQ_FINE:
      m_freq_fine2->setNumber(core->getParameter(REQ_VALUE_RAW, m_sw_freq2) +
                              core->getParameter(REQ_VALUE_RAW, m_sw_freq_fine2));
      m_events.addEvent(m_freq_fine2, DEF_TICKS, 0);
      break;
    
    // ADSR stuff
    case PRM_1_ATTACK:
    case PRM_2_ATTACK:
      m_attack1->setNumber(core->getParameter(REQ_VALUE_RAW, m_sw_attack1, NULL));
      m_events.addEvent(m_attack1, DEF_TICKS, 0);
      lset = true;
            
    case PRM_1_ATTACK_AMP:
    case PRM_2_ATTACK_AMP:
      if(!lset) {
        m_attack_amp1->setNumber(core->getParameter(REQ_VALUE_RAW, m_sw_attack_amp1, NULL));
        m_events.addEvent(m_attack_amp1, DEF_TICKS, 0);
        lset = true;
      }
      m_adsr1->setAttackCoords(core->getParameter(REQ_VALUE_RAW, m_sw_attack1, NULL),
                               core->getParameter(REQ_VALUE_RAW, m_sw_attack_amp1, NULL));
    case PRM_1_DECAY:
    case PRM_2_DECAY:
      if(!lset) {
        m_decay1->setNumber(core->getParameter(REQ_VALUE_RAW, m_sw_decay1, NULL));
        m_events.addEvent(m_decay1, DEF_TICKS, 0);
        lset = true;
      }
    case PRM_1_DECAY_AMP:
    case PRM_2_DECAY_AMP:
      if(!lset) {
        m_decay_amp1->setNumber(core->getParameter(REQ_VALUE_RAW, m_sw_decay_amp1, NULL));
        m_events.addEvent(m_decay_amp1, DEF_TICKS, 0);
        lset = true;
      }
      m_adsr1->setDecayCoords(core->getParameter(REQ_VALUE_RAW, m_sw_decay1, NULL),
                              core->getParameter(REQ_VALUE_RAW, m_sw_decay_amp1, NULL));
    case PRM_1_SUSTAIN:
    case PRM_2_SUSTAIN:
      if(!lset) {
        m_sustain1->setNumber(core->getParameter(REQ_VALUE_RAW, m_sw_sustain1, NULL));
        m_events.addEvent(m_sustain1, DEF_TICKS, 0);
        lset = true;
      }
    case PRM_1_SUSTAIN_AMP:
    case PRM_2_SUSTAIN_AMP:
      if(!lset) {
        m_sustain_amp1->setNumber(core->getParameter(REQ_VALUE_RAW, m_sw_sustain_amp1, NULL));
        m_events.addEvent(m_sustain_amp1, DEF_TICKS, 0);
        lset = true;
      }
      m_adsr1->setSustainCoords(core->getParameter(REQ_VALUE_RAW, m_sw_sustain1, NULL),
                                core->getParameter(REQ_VALUE_RAW, m_sw_sustain_amp1, NULL));
    case PRM_1_RELEASE:
    case PRM_2_RELEASE:
      if(!lset) {
        m_release1->setNumber(core->getParameter(REQ_VALUE_RAW, m_sw_release1, NULL));
        m_events.addEvent(m_release1, DEF_TICKS, 0);
        lset = true;
      }
      m_adsr1->setReleaseCoords(core->getParameter(REQ_VALUE_RAW, m_sw_release1, NULL), 0.0);
      break;
      
    case PRM_3_ATTACK:
    case PRM_4_ATTACK:
      if(!lset) {
        m_attack2->setNumber(core->getParameter(REQ_VALUE_RAW, m_sw_attack2, NULL));
        m_events.addEvent(m_attack2, DEF_TICKS, 0);
        lset = true;
      }
    case PRM_3_ATTACK_AMP:
    case PRM_4_ATTACK_AMP:
      if(!lset) {
        m_attack_amp2->setNumber(core->getParameter(REQ_VALUE_RAW, m_sw_attack_amp2, NULL));
        m_events.addEvent(m_attack_amp2, DEF_TICKS, 0);
        lset = true;
      }
      m_adsr2->setAttackCoords(core->getParameter(REQ_VALUE_RAW, m_sw_attack2, NULL),
                               core->getParameter(REQ_VALUE_RAW, m_sw_attack_amp2, NULL));
    case PRM_3_DECAY:
    case PRM_4_DECAY:
      if(!lset) {
        m_decay2->setNumber(core->getParameter(REQ_VALUE_RAW, m_sw_decay2, NULL));
        m_events.addEvent(m_decay2, DEF_TICKS, 0);
        lset = true;
      }
    case PRM_3_DECAY_AMP:
    case PRM_4_DECAY_AMP:
      if(!lset) {
        m_decay_amp2->setNumber(core->getParameter(REQ_VALUE_RAW, m_sw_decay_amp2, NULL));
        m_events.addEvent(m_decay_amp2, DEF_TICKS, 0);
        lset = true;
      }
      m_adsr2->setDecayCoords(core->getParameter(REQ_VALUE_RAW, m_sw_decay2, NULL),
                              core->getParameter(REQ_VALUE_RAW, m_sw_decay_amp2, NULL));
    case PRM_3_SUSTAIN:
    case PRM_4_SUSTAIN:
      if(!lset) {
        m_sustain2->setNumber(core->getParameter(REQ_VALUE_RAW, m_sw_sustain2, NULL));
        m_events.addEvent(m_sustain2, DEF_TICKS, 0);
        lset = true;
      }
    case PRM_3_SUSTAIN_AMP:
    case PRM_4_SUSTAIN_AMP:
      if(!lset) {
        m_sustain_amp2->setNumber(core->getParameter(REQ_VALUE_RAW, m_sw_sustain_amp2, NULL));
        m_events.addEvent(m_sustain_amp2, DEF_TICKS, 0);
        lset = true;
      }
      m_adsr2->setSustainCoords(core->getParameter(REQ_VALUE_RAW, m_sw_sustain2, NULL),
                                core->getParameter(REQ_VALUE_RAW, m_sw_sustain_amp2, NULL));
    case PRM_3_RELEASE:
    case PRM_4_RELEASE:
      if(!lset) {
        m_release2->setNumber(core->getParameter(REQ_VALUE_RAW, m_sw_release2, NULL));
        m_events.addEvent(m_release2, DEF_TICKS, 0);
        lset = true;
      }
      m_adsr2->setReleaseCoords(core->getParameter(REQ_VALUE_RAW, m_sw_release2, NULL), 0.0);
      break;
      
    case PRM_ALL_ATTACK:
      if(!lset) {
        m_attack->setNumber(core->getParameter(REQ_VALUE_RAW, PRM_ALL_ATTACK, NULL));
        m_events.addEvent(m_attack, DEF_TICKS, 0);
        lset = true;
      }
    case PRM_ALL_ATTACK_AMP:
      if(!lset) {
        m_attack_amp->setNumber(core->getParameter(REQ_VALUE_RAW, PRM_ALL_ATTACK_AMP, NULL));
        m_events.addEvent(m_attack_amp, DEF_TICKS, 0);
        lset = true;
      }
      m_adsr->setAttackCoords(core->getParameter(REQ_VALUE_RAW, PRM_ALL_ATTACK, NULL),
                              core->getParameter(REQ_VALUE_RAW, PRM_ALL_ATTACK_AMP, NULL));
    case PRM_ALL_DECAY:
      if(!lset) {
        m_decay->setNumber(core->getParameter(REQ_VALUE_RAW, PRM_ALL_DECAY, NULL));
        m_events.addEvent(m_decay, DEF_TICKS, 0);
        lset = true;
      }
    case PRM_ALL_DECAY_AMP:
      if(!lset) {
        m_decay_amp->setNumber(core->getParameter(REQ_VALUE_RAW, PRM_ALL_DECAY_AMP, NULL));
        m_events.addEvent(m_decay_amp, DEF_TICKS, 0);
        lset = true;
      }
      m_adsr->setDecayCoords(core->getParameter(REQ_VALUE_RAW, PRM_ALL_DECAY, NULL),
                             core->getParameter(REQ_VALUE_RAW, PRM_ALL_DECAY_AMP, NULL));
    case PRM_ALL_SUSTAIN:
      if(!lset) {
        m_sustain->setNumber(core->getParameter(REQ_VALUE_RAW, PRM_ALL_SUSTAIN, NULL));
        m_events.addEvent(m_sustain, DEF_TICKS, 0);
        lset = true;
      }
    case PRM_ALL_SUSTAIN_AMP:
      if(!lset) {
        m_sustain_amp->setNumber(core->getParameter(REQ_VALUE_RAW, PRM_ALL_SUSTAIN_AMP, NULL));
        m_events.addEvent(m_sustain_amp, DEF_TICKS, 0);
        lset = true;
      }
      m_adsr->setSustainCoords(core->getParameter(REQ_VALUE_RAW, PRM_ALL_SUSTAIN, NULL),
                               core->getParameter(REQ_VALUE_RAW, PRM_ALL_SUSTAIN_AMP, NULL));
    case PRM_ALL_RELEASE:
      if(!lset) {
        m_release->setNumber(core->getParameter(REQ_VALUE_RAW, PRM_ALL_RELEASE, NULL));
        m_events.addEvent(m_release, DEF_TICKS, 0);
        lset = true;
      }
      m_adsr->setReleaseCoords(core->getParameter(REQ_VALUE_RAW, PRM_ALL_RELEASE, NULL), 0.0);
      break;
      
    case TAG_ALL_ADSR:
    {
      CPoint p;
      CRect r;
      pControl->getViewSize(r);
      pControl->getMouseLocation(pContext, p);
      
      if(p.h < r.left) {
        p.h = r.left;
      }
      else if(p.h > r.right) {
        p.h = r.right;
      }
      if(p.v > r.bottom) {
        p.v = r.bottom;
      }
      else if(p.v < r.top) {
        p.v = r.top;
      }
      
      printf("You picked point %d @ %d, %d\n", (int)pControl->getValue(), p.h, p.v);
      float x = (float)(p.h - r.left) / (float)r.width();
      float y = 1.0 - (float)(p.v - r.top) / (float)r.height();
      
      bool lset = false;
      switch((int)pControl->getValue())
      {
        case 1:
          m_attack->setValue(x);
          m_attack_amp->setValue(y);
          setParameter(PRM_ALL_ATTACK, x);
          setParameter(PRM_ALL_ATTACK_AMP, y);
          m_adsr->setAttackCoords(core->getParameter(REQ_VALUE_RAW, PRM_ALL_ATTACK, NULL),
                                  core->getParameter(REQ_VALUE_RAW, PRM_ALL_ATTACK_AMP, NULL));
          lset = true;
        case 2:
          if(!lset)
          {
            m_decay->setValue(x);
            m_decay_amp->setValue(y);
            setParameter(PRM_ALL_DECAY, x);
            setParameter(PRM_ALL_DECAY_AMP, y);
            lset = true;
          }
          m_adsr->setDecayCoords(core->getParameter(REQ_VALUE_RAW, PRM_ALL_DECAY, NULL),
                                 core->getParameter(REQ_VALUE_RAW, PRM_ALL_DECAY_AMP, NULL));
        case 3:
          if(!lset)
          {
            m_sustain->setValue(x);
            m_sustain_amp->setValue(y);
            setParameter(PRM_ALL_SUSTAIN, x);
            setParameter(PRM_ALL_SUSTAIN_AMP, y);
            lset = true;
          }
          m_adsr->setSustainCoords(core->getParameter(REQ_VALUE_RAW, PRM_ALL_SUSTAIN, NULL),
                                   core->getParameter(REQ_VALUE_RAW, PRM_ALL_SUSTAIN_AMP, NULL));
          m_adsr->setReleaseCoords(core->getParameter(REQ_VALUE_RAW, PRM_ALL_RELEASE, NULL), 0.0);

          break;
        default:
          break;
      }
    }
      break;
      
    default:
      break;
  }
}

// AU VSTGUI hooks ///////////////////////////////////////////////////////////////////////

#ifdef USE_PC_AU
COMPONENT_ENTRY(KickMakerView);

KickMakerView::KickMakerView(AudioUnitCarbonView auv) 
: AUCarbonViewBase(auv), editor(0), xOffset(0), yOffset(0) {
}

KickMakerView::~KickMakerView() {
  if(editor) {
    editor->close();
  }
}

void KickMakerView::RespondToEventTimer(EventLoopTimerRef inTimer) {
  if(editor) {
    editor->idle();
  }
}

OSStatus KickMakerView::CreateUI(Float32 xoffset, Float32 yoffset) {
  AudioUnit unit = GetEditAudioUnit();
  if(unit) {
    editor = new KickMakerEditor(unit);
    editor->setAU(unit);
    
    UInt32 size;
    Boolean write;
    if(AudioUnitGetPropertyInfo(unit, PRP_CORE, kAudioUnitScope_Global, 0, &size, &write) == noErr) {
      pluginCore *p[1];
      if(AudioUnitGetProperty(unit, PRP_CORE, kAudioUnitScope_Global, 0, p, &size) == noErr) {
        editor->setCore(p[0]);
      }
      else {
        // Core couldn't be set
        return -1;
      }
    }
    else {
      // Core property information couldn't be obtained
      return -1;
    }
    
    if(AudioUnitSetProperty(unit, PRP_EDITOR, kAudioUnitScope_Global, 0,
                            editor, sizeof(KickMakerEditor*)) != noErr) {
      // Something failed here..
      return -1;
    }
    
    WindowRef window = GetCarbonWindow();
    editor->open(window);
    HIViewMoveBy((HIViewRef)editor->getFrame()->getPlatformControl(), xoffset, yoffset);
    EmbedControl((HIViewRef)editor->getFrame()->getPlatformControl());
    CRect fsize = editor->getFrame()->getViewSize(fsize);
    SizeControl(mCarbonPane, fsize.width(), fsize.height());
    CreateEventLoopTimer(kEventDurationSecond, kEventDurationSecond / 24);
    HIViewSetVisible((HIViewRef)editor->getFrame()->getPlatformControl(), true);
    HIViewSetNeedsDisplay((HIViewRef)editor->getFrame()->getPlatformControl(), true);
  }
  return noErr;
}
#endif