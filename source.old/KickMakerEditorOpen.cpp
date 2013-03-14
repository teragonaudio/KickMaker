/*
 *  KickMakerEditorOpen.cpp
 *  KickMaker
 *
 *  Created by Nik Reiman on 18.02.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __KickMakerEditor_H
#include "KickMakerEditor.h"
#endif

bool KickMakerEditor::open(void *ptr) {
  AEffGUIEditor::open(ptr);
  m_window = ptr;
  
  // m_logger->logS(1017);
  CRect size(0, 0, m_background->getWidth(), m_background->getHeight());
  frame = new CFrame(size, ptr, this);
  frame->setBackground(m_background);
  
  if(core == NULL) {
    return false;
  }
  
  // m_logger->logS(1018);
  CPoint point(0, 0);
  CBitmap *kbig, *ksmall, *btn, *vhandle, *meterhandle,
          *fxknob, *bfont, *nfont;
  btn = new CBitmap(REZ_BUTTON);
  kbig = new CBitmap(REZ_KNOB_BIG);
  ksmall = new CBitmap(REZ_KNOB_SMALL);
  vhandle = new CBitmap(REZ_SLIDER_HANDLE);
  meterhandle = new CBitmap(REZ_METER_HANDLE);
  fxknob = new CBitmap(REZ_EFFECT_KNOB);
  bfont = new CBitmap(REZ_BITMAP_FONT);
  nfont = new CBitmap(REZ_NUMBER_FONT);

  int ksmallw = ksmall->getWidth();
  int kbigw = kbig->getWidth();
  
  // Effect displays ///////////////////////////////////////////////////////////////////
    
  // Effect 1-1
  // m_logger->logS(1019);
  setCoords(TAG_1_EFFECT_LABEL1, size, DEF_EFFECT_LABEL_WIDTH, DEF_EFFECT_LABEL_HEIGHT);
  m_effect_label1_1 = new cKeyedOptionMenu(size, this, TAG_1_EFFECT_LABEL1);
  addMenuOptions(m_effect_label1_1);
  m_effect_label1_1->setValue(8);
  frame->addView(m_effect_label1_1);
  
  CBitmap *rfont = bfont; // new CBitmap(REZ_EFFECT_FONT);
  setCoords(TAG_1_EFFECT_METER1, size, DEF_EFFECT_LABEL_WIDTH, DEF_EFFECT_LABEL_HEIGHT);
  m_effect_meter_vu1_1 = new cLevelDisplayBitmap(size, this, -1, 0, rfont, DEF_DISPLAY_OFFSET_X, DEF_DISPLAY_OFFSET_Y);
  frame->addView(m_effect_meter_vu1_1);
  
  m_effect_meter1_1 = new CHorizontalSlider(size, this, TAG_1_EFFECT_METER1, point, size.width(),
                                            meterhandle, 0, point, kLeft);
  m_effect_meter1_1->setTransparency(true);
  frame->addView(m_effect_meter1_1);
  
  setCoords(TAG_1_EFFECT_KNOB1, size, fxknob->getWidth(), fxknob->getWidth());
  m_effect_knob1_1 = new CAnimKnob(size, this, TAG_1_EFFECT_KNOB1, DEF_NUM_FRAMES, fxknob->getWidth(),
                                    fxknob, point);
  frame->addView(m_effect_knob1_1);
  
  // Effect 1-2
  // m_logger->logS(1020);
  setCoords(TAG_1_EFFECT_LABEL2, size, DEF_EFFECT_LABEL_WIDTH, DEF_EFFECT_LABEL_HEIGHT);
  m_effect_label1_2 = new cKeyedOptionMenu(size, this, TAG_1_EFFECT_LABEL2);
  addMenuOptions(m_effect_label1_2);
  m_effect_label1_2->setValue(12);
  frame->addView(m_effect_label1_2);
  
  setCoords(TAG_1_EFFECT_METER2, size, DEF_EFFECT_LABEL_WIDTH, DEF_EFFECT_LABEL_HEIGHT);
  m_effect_meter_vu1_2 = new cLevelDisplayBitmap(size, this, -1, 0, rfont, DEF_DISPLAY_OFFSET_X, DEF_DISPLAY_OFFSET_Y);
  frame->addView(m_effect_meter_vu1_2);
  
  m_effect_meter1_2 = new CHorizontalSlider(size, this, TAG_1_EFFECT_METER2, point, size.width(),
                                            meterhandle, 0, point, kLeft);
  m_effect_meter1_2->setTransparency(true);
  frame->addView(m_effect_meter1_2);
  
  setCoords(TAG_1_EFFECT_KNOB2, size, fxknob->getWidth(), fxknob->getWidth());
  m_effect_knob1_2 = new CAnimKnob(size, this, TAG_1_EFFECT_KNOB2, DEF_NUM_FRAMES, fxknob->getWidth(),
                                    fxknob, point);
  frame->addView(m_effect_knob1_2);
  
  // Effect 1-3
  // m_logger->logS(1021);
  setCoords(TAG_1_EFFECT_LABEL3, size, DEF_EFFECT_LABEL_WIDTH, DEF_EFFECT_LABEL_HEIGHT);
  m_effect_label1_3 = new cKeyedOptionMenu(size, this, TAG_1_EFFECT_LABEL3);
  addMenuOptions(m_effect_label1_3);
  m_effect_label1_3->setValue(18);
  frame->addView(m_effect_label1_3);
  
  setCoords(TAG_1_EFFECT_METER3, size, DEF_EFFECT_LABEL_WIDTH, DEF_EFFECT_LABEL_HEIGHT);
  m_effect_meter_vu1_3 = new cLevelDisplayBitmap(size, this, -1, 0, rfont, DEF_DISPLAY_OFFSET_X, DEF_DISPLAY_OFFSET_Y);
  frame->addView(m_effect_meter_vu1_3);
  
  m_effect_meter1_3 = new CHorizontalSlider(size, this, TAG_1_EFFECT_METER3, point, size.width(),
                                            meterhandle, 0, point, kLeft);
  m_effect_meter1_3->setTransparency(true);
  frame->addView(m_effect_meter1_3);
  
  setCoords(TAG_1_EFFECT_KNOB3, size, fxknob->getWidth(), fxknob->getWidth());
  m_effect_knob1_3 = new CAnimKnob(size, this, TAG_1_EFFECT_KNOB3, DEF_NUM_FRAMES, fxknob->getWidth(),
                                    fxknob, point);
  frame->addView(m_effect_knob1_3);
  
  // Effect 2-1
  // m_logger->logS(1022);
  setCoords(TAG_2_EFFECT_LABEL1, size, DEF_EFFECT_LABEL_WIDTH, DEF_EFFECT_LABEL_HEIGHT);
  m_effect_label2_1 = new cKeyedOptionMenu(size, this, TAG_2_EFFECT_LABEL1);
  addMenuOptions(m_effect_label2_1);
  m_effect_label2_1->setValue(9);
  frame->addView(m_effect_label2_1);
  
  setCoords(TAG_2_EFFECT_METER1, size, DEF_EFFECT_LABEL_WIDTH, DEF_EFFECT_LABEL_HEIGHT);
  m_effect_meter_vu2_1 = new cLevelDisplayBitmap(size, this, -1, 0, rfont, DEF_DISPLAY_OFFSET_X, DEF_DISPLAY_OFFSET_Y);
  frame->addView(m_effect_meter_vu2_1);
  
  m_effect_meter2_1 = new CHorizontalSlider(size, this, TAG_2_EFFECT_METER1, point, size.width(),
                                            meterhandle, 0, point, kLeft);
  m_effect_meter2_1->setTransparency(true);
  frame->addView(m_effect_meter2_1);
  
  setCoords(TAG_2_EFFECT_KNOB1, size, fxknob->getWidth(), fxknob->getWidth());
  m_effect_knob2_1 = new CAnimKnob(size, this, TAG_2_EFFECT_KNOB1, DEF_NUM_FRAMES, fxknob->getWidth(),
                                    fxknob, point);
  frame->addView(m_effect_knob2_1);
  
  // Effect 2-2
  // m_logger->logS(1023);
  setCoords(TAG_2_EFFECT_LABEL2, size, DEF_EFFECT_LABEL_WIDTH, DEF_EFFECT_LABEL_HEIGHT);
  m_effect_label2_2 = new cKeyedOptionMenu(size, this, TAG_2_EFFECT_LABEL2);
  addMenuOptions(m_effect_label2_2);
  m_effect_label2_2->setValue(13);
  frame->addView(m_effect_label2_2);
  
  setCoords(TAG_2_EFFECT_METER2, size, DEF_EFFECT_LABEL_WIDTH, DEF_EFFECT_LABEL_HEIGHT);
  m_effect_meter_vu2_2 = new cLevelDisplayBitmap(size, this, -1, 0, rfont, DEF_DISPLAY_OFFSET_X, DEF_DISPLAY_OFFSET_Y);
  frame->addView(m_effect_meter_vu2_2);
  
  m_effect_meter2_2 = new CHorizontalSlider(size, this, TAG_2_EFFECT_METER2, point, size.width(),
                                            meterhandle, 0, point, kLeft);
  m_effect_meter2_2->setTransparency(true);
  frame->addView(m_effect_meter2_2);
  
  setCoords(TAG_2_EFFECT_KNOB2, size, fxknob->getWidth(), fxknob->getWidth());
  m_effect_knob2_2 = new CAnimKnob(size, this, TAG_2_EFFECT_KNOB2, DEF_NUM_FRAMES, fxknob->getWidth(),
                                    fxknob, point);
  frame->addView(m_effect_knob2_2);
  
  // Effect 2-3
  // m_logger->logS(1024);
  setCoords(TAG_2_EFFECT_LABEL3, size, DEF_EFFECT_LABEL_WIDTH, DEF_EFFECT_LABEL_HEIGHT);
  m_effect_label2_3 = new cKeyedOptionMenu(size, this, TAG_2_EFFECT_LABEL3);
  addMenuOptions(m_effect_label2_3);
  m_effect_label2_3->setValue(19);
  frame->addView(m_effect_label2_3);
  
  setCoords(TAG_2_EFFECT_METER3, size, DEF_EFFECT_LABEL_WIDTH, DEF_EFFECT_LABEL_HEIGHT);
  m_effect_meter_vu2_3 = new cLevelDisplayBitmap(size, this, -1, 0, rfont, DEF_DISPLAY_OFFSET_X, DEF_DISPLAY_OFFSET_Y);
  frame->addView(m_effect_meter_vu2_3);
  
  m_effect_meter2_3 = new CHorizontalSlider(size, this, TAG_2_EFFECT_METER3, point, size.width(),
                                            meterhandle, 0, point, kLeft);
  m_effect_meter2_3->setTransparency(true);
  frame->addView(m_effect_meter2_3);
  
  setCoords(TAG_2_EFFECT_KNOB3, size, fxknob->getWidth(), fxknob->getWidth());
  m_effect_knob2_3 = new CAnimKnob(size, this, TAG_2_EFFECT_KNOB3, DEF_NUM_FRAMES, fxknob->getWidth(),
                                    fxknob, point);
  frame->addView(m_effect_knob2_3);
  
  // Preset Display ///////////////////////////////////////////////////////////////
  
  // m_logger->logS(1025);
  setCoords(TAG_PRESET_DISPLAY, size, 108, 10);
  m_preset_edit = new cTextEditLockable(size, this, TAG_PRESET_DISPLAY, 0, 0, 0);
  frame->addView(m_preset_edit);
  
  m_preset_label = new cBitmapFont(size, this, TAG_PRESET_DISPLAY, bfont, 2, 1 + 10 + 26 + 26 + 2);
  char cbuf[32];
  core->getCurrentPresetName((char*)&cbuf);
  m_preset_label->setText(cbuf);
  frame->addView(m_preset_label);
  m_preset_label->setDirty();

  m_preset_menu = new cOptionMenuHidden(size, this, TAG_PRESET_MENU);
  fillPresetMenu(m_preset_menu);
  frame->addView(m_preset_menu);
  
  CBitmap *savebtn = new CBitmap(REZ_SAVE_BUTTON);
  setCoords(TAG_SAVE_BUTTON, size, savebtn->getWidth(), savebtn->getHeight() / 2);
  m_save_button = new CKickButton(size, this, TAG_SAVE_BUTTON, savebtn, point);
  frame->addView(m_save_button);
  
  CBitmap *delbtn = new CBitmap(REZ_DELETE_BUTTON);
  setCoords(TAG_DELETE_BUTTON, size, delbtn->getWidth(), delbtn->getHeight() / 2);
  m_delete_button = new CKickButton(size, this, TAG_DELETE_BUTTON, delbtn, point);
  frame->addView(m_delete_button);
  
  CBitmap *nextbtn = new CBitmap(REZ_NEXT_BUTTON);
  setCoords(TAG_NEXT_BUTTON, size, nextbtn->getWidth(), nextbtn->getHeight() / 2);
  m_next_button = new CKickButton(size, this, TAG_NEXT_BUTTON, nextbtn, point);
  frame->addView(m_next_button);
  
  CBitmap *prevbtn = new CBitmap(REZ_PREV_BUTTON);
  setCoords(TAG_PREV_BUTTON, size, prevbtn->getWidth(), prevbtn->getHeight() / 2);
  m_prev_button = new CKickButton(size, this, TAG_PREV_BUTTON, prevbtn, point);
  frame->addView(m_prev_button);
  
  // Voice 1 Controls ////////////////////////////////////////////////////////////////
  // m_logger->logS(1026);
  
  // Enabled button
  if(setCoords(PRM_1_ENABLED, size, btn->getWidth(), btn->getHeight() / 2)) {
    m_enabled1 = new COnOffButton(size, this, m_sw_enabled1, btn, 0);
    m_enabled1->setValue(0.0);
    frame->addView(m_enabled1);
  }
  
  // Oscillator switch
  CBitmap *oscbutton1 = new CBitmap(REZ_OSC_SW_1);
  if(setCoords(TAG_1_SWITCH, size, oscbutton1->getWidth(), oscbutton1->getHeight() / 2)) {
    m_switch1 = new COnOffButton(size, this, TAG_1_SWITCH, oscbutton1, 0);
    frame->addView(m_switch1);
  }
  oscbutton1->forget();
  
  // Freq knob
  if(setCoords(PRM_1_FREQ, size, kbigw, kbigw + 2 + (nfont->getHeight() / 12))) {
    m_freq1 = new cSmartKnob(size, this, m_sw_freq1, DEF_NUM_FRAMES, kbig->getWidth(), kbig,
                             nfont, point, frame);
    m_freq1->setPrecision(3, 1);
    frame->addView(m_freq1);
  }
  
  // Attack knob
  if(setCoords(PRM_1_ATTACK, size, kbigw, kbigw + 2 + (nfont->getHeight() / 12))) {
    m_attack1 = new cSmartKnob(size, this, m_sw_attack1, DEF_NUM_FRAMES, kbig->getWidth(), kbig,
                               nfont, point, frame);
    frame->addView(m_attack1);
  }
  
  // Decay knob
  if(setCoords(PRM_1_DECAY, size, kbigw, kbigw + 2 + (nfont->getHeight() / 12))) {
    m_decay1 = new cSmartKnob(size, this, m_sw_decay1, DEF_NUM_FRAMES, kbig->getWidth(), kbig,
                              nfont, point, frame);
    frame->addView(m_decay1);
  }
  
  // Sustain knob
  if(setCoords(PRM_1_SUSTAIN, size, kbigw, kbigw + 2 + (nfont->getHeight() / 12))) {
    m_sustain1 = new cSmartKnob(size, this, m_sw_sustain1, DEF_NUM_FRAMES, kbig->getWidth(), kbig,
                                nfont, point, frame);
    frame->addView(m_sustain1);
  }
  
  // Release knob
  if(setCoords(PRM_1_RELEASE, size, kbigw, kbigw + 2 + (nfont->getHeight() / 12))) {
    m_release1 = new cSmartKnob(size, this, m_sw_release1, DEF_NUM_FRAMES, kbig->getWidth(), kbig,
                                nfont, point, frame);
    frame->addView(m_release1);
  }
  
  // Freq fine
  if(setCoords(PRM_1_FREQ_FINE, size, ksmallw, ksmallw + 2 + (nfont->getHeight() / 12))) {
    m_freq_fine1 = new cSmartKnob(size, this, m_sw_freq_fine1, DEF_NUM_FRAMES,
                                  ksmall->getWidth(), ksmall, nfont, point, frame);
    m_freq_fine1->setPrecision(3, 1);
    frame->addView(m_freq_fine1);
  }
  
  // Attack amp
  if(setCoords(PRM_1_ATTACK_AMP, size, ksmallw, ksmallw + 2 + (nfont->getHeight() / 12))) {
    m_attack_amp1 = new cSmartKnob(size, this, m_sw_attack_amp1, DEF_NUM_FRAMES,
                                  ksmall->getWidth(), ksmall, nfont, point, frame);
    frame->addView(m_attack_amp1);
  }
  
  // Decay amp
  if(setCoords(PRM_1_DECAY_AMP, size, ksmallw, ksmallw + 2 + (nfont->getHeight() / 12))) {
    m_decay_amp1 = new cSmartKnob(size, this, m_sw_decay_amp1, DEF_NUM_FRAMES,
                                 ksmall->getWidth(), ksmall, nfont, point, frame);
    frame->addView(m_decay_amp1);
  }
  
  // Sustain amp
  if(setCoords(PRM_1_SUSTAIN_AMP, size, ksmallw, ksmallw + 2 + (nfont->getHeight() / 12))) {
    m_sustain_amp1 = new cSmartKnob(size, this, m_sw_sustain_amp1, DEF_NUM_FRAMES,
                                   ksmall->getWidth(), ksmall, nfont, point, frame);
    frame->addView(m_sustain_amp1);
  }
  
  // ADSR display
  if(setCoords(TAG_1_ADSR, size, DEF_ADSR_WIDTH, DEF_ADSR_HEIGHT)) {
    m_adsr1 = new cADSRDisplay(size, this, TAG_1_ADSR, 0);
    frame->addView(m_adsr1);
  }
  
  // Voice 2 Controls ////////////////////////////////////////////////////////////////
  // m_logger->logS(1027);
  
  // Enabled button
  if(setCoords(PRM_2_ENABLED, size, btn->getWidth(), btn->getHeight() / 2)) {
    m_enabled2 = new COnOffButton(size, this, m_sw_enabled2, btn, 0);
    m_enabled2->setValue(0.0);
    frame->addView(m_enabled2);
  }
  
  // Oscillator switch
  CBitmap *oscbutton2 = new CBitmap(REZ_OSC_SW_2);
  if(setCoords(TAG_2_SWITCH, size, oscbutton2->getWidth(), oscbutton2->getHeight() / 2)) {
    m_switch2 = new COnOffButton(size, this, TAG_2_SWITCH, oscbutton2, 0);
    frame->addView(m_switch2);
  }
  oscbutton2->forget();
  
  // Freq knob
  if(setCoords(PRM_2_FREQ, size, kbigw, kbigw + 2 + (nfont->getHeight() / 12))) {
    m_freq2 = new cSmartKnob(size, this, m_sw_freq2, DEF_NUM_FRAMES, kbig->getWidth(), kbig,
                             nfont, point, frame);
    m_freq2->setPrecision(3, 1);
    frame->addView(m_freq2);
  }
  
  // Attack knob
  if(setCoords(PRM_2_ATTACK, size, kbigw, kbigw + 2 + (nfont->getHeight() / 12))) {
    m_attack2 = new cSmartKnob(size, this, m_sw_attack2, DEF_NUM_FRAMES, kbig->getWidth(), kbig,
                               nfont, point, frame);
    frame->addView(m_attack2);
  }
  
  // Decay knob
  if(setCoords(PRM_2_DECAY, size, kbigw, kbigw + 2 + (nfont->getHeight() / 12))) {
    m_decay2 = new cSmartKnob(size, this, m_sw_decay2, DEF_NUM_FRAMES, kbig->getWidth(), kbig,
                              nfont, point, frame);
    frame->addView(m_decay2);
  }
  
  // Sustain knob
  if(setCoords(PRM_2_SUSTAIN, size, kbigw, kbigw + 2 + (nfont->getHeight() / 12))) {
    m_sustain2 = new cSmartKnob(size, this, m_sw_sustain2, DEF_NUM_FRAMES, kbig->getWidth(), kbig,
                                nfont, point, frame);
    frame->addView(m_sustain2);
  }
  
  // Release knob
  if(setCoords(PRM_2_RELEASE, size, kbigw, kbigw + 2 + (nfont->getHeight() / 12))) {
    m_release2 = new cSmartKnob(size, this, m_sw_release2, DEF_NUM_FRAMES, kbig->getWidth(), kbig,
                                nfont, point, frame);
    frame->addView(m_release2);
  }
  
  // Freq fine
  if(setCoords(PRM_2_FREQ_FINE, size, ksmallw, ksmallw + 2 + (nfont->getHeight() / 12))) {
    m_freq_fine2 = new cSmartKnob(size, this, m_sw_freq_fine2, DEF_NUM_FRAMES,
                                  ksmall->getWidth(), ksmall, nfont, point, frame);
    m_freq_fine2->setPrecision(3, 1);
    frame->addView(m_freq_fine2);
  }
  
  // Attack amp
  if(setCoords(PRM_2_ATTACK_AMP, size, ksmallw, ksmallw + 2 + (nfont->getHeight() / 12))) {
    m_attack_amp2 = new cSmartKnob(size, this, m_sw_attack_amp2, DEF_NUM_FRAMES,
                                  ksmall->getWidth(), ksmall, nfont, point, frame);
    frame->addView(m_attack_amp2);
  }
  
  // Decay amp
  if(setCoords(PRM_2_DECAY_AMP, size, ksmallw, ksmallw + 2 + (nfont->getHeight() / 12))) {
    m_decay_amp2 = new cSmartKnob(size, this, m_sw_decay_amp2, DEF_NUM_FRAMES,
                                 ksmall->getWidth(), ksmall, nfont, point, frame);
    frame->addView(m_decay_amp2);
  }
  
  // Sustain amp
  if(setCoords(PRM_2_SUSTAIN_AMP, size, ksmallw, ksmallw + 2 + (nfont->getHeight() / 12))) {
    m_sustain_amp2 = new cSmartKnob(size, this, m_sw_sustain_amp2, DEF_NUM_FRAMES,
                                   ksmall->getWidth(), ksmall, nfont, point, frame);
    frame->addView(m_sustain_amp2);
  }
  
  // ADSR display
  if(setCoords(TAG_2_ADSR, size, DEF_ADSR_WIDTH, DEF_ADSR_HEIGHT)) {
    m_adsr2 = new cADSRDisplay(size, this, TAG_2_ADSR, 0);
    frame->addView(m_adsr2);
  }
  
  // Volumes
  if(setCoords(PRM_1_VOLUME, size, vhandle->getWidth(), DEF_SLIDER_AMOUNT)) {
    m_volume1 = new CVerticalSlider(size, this, PRM_1_VOLUME, point, size.height(),
                                    vhandle, 0, point, kBottom);
    m_volume1->setTransparency(true);
    frame->addView(m_volume1);
  }
  
  if(setCoords(PRM_2_VOLUME, size, vhandle->getWidth(), DEF_SLIDER_AMOUNT)) {
    m_volume2 = new CVerticalSlider(size, this, PRM_2_VOLUME, point, size.height(),
                                    vhandle, 0, point, kBottom);
    m_volume2->setTransparency(true);
    frame->addView(m_volume2);
  }
  
  if(setCoords(PRM_3_VOLUME, size, vhandle->getWidth(), DEF_SLIDER_AMOUNT)) {
    m_volume3 = new CVerticalSlider(size, this, PRM_3_VOLUME, point, size.height(),
                                    vhandle, 0, point, kBottom);
    m_volume3->setTransparency(true);
    frame->addView(m_volume3);
  }
  
  if(setCoords(PRM_4_VOLUME, size, vhandle->getWidth(), DEF_SLIDER_AMOUNT)) {
    m_volume4 = new CVerticalSlider(size, this, PRM_4_VOLUME, point, size.height(),
                                    vhandle, 0, point, kBottom);
    m_volume4->setTransparency(true);
    frame->addView(m_volume4);
  }
  
  if(setCoords(PRM_ALL_VOLUME, size, vhandle->getWidth(), DEF_SLIDER_AMOUNT)) {
    m_volume = new CVerticalSlider(size, this, PRM_ALL_VOLUME, point, size.height(),
                                   vhandle, 0, point, kBottom);
    m_volume->setTransparency(true);
    frame->addView(m_volume);
  }
  
  // Global Controls ////////////////////////////////////////////////////////////////
  // m_logger->logS(1028);
  
  // Attack knob
  if(setCoords(PRM_ALL_ATTACK, size, kbigw, kbigw + 2 + (nfont->getHeight() / 12))) {
    m_attack = new cSmartKnob(size, this, PRM_ALL_ATTACK, DEF_NUM_FRAMES, kbig->getWidth(), kbig,
                              nfont, point, frame);
    frame->addView(m_attack);
  }
  
  // Decay knob
  if(setCoords(PRM_ALL_DECAY, size, kbigw, kbigw + 2 + (nfont->getHeight() / 12))) {
    m_decay = new cSmartKnob(size, this, PRM_ALL_DECAY, DEF_NUM_FRAMES, kbig->getWidth(), kbig,
                             nfont, point, frame);
    frame->addView(m_decay);
  }
  
  // Sustain knob
  if(setCoords(PRM_ALL_SUSTAIN, size, kbigw, kbigw + 2 + (nfont->getHeight() / 12))) {
    m_sustain = new cSmartKnob(size, this, PRM_ALL_SUSTAIN, DEF_NUM_FRAMES, kbig->getWidth(), kbig,
                               nfont, point, frame);
    frame->addView(m_sustain);
  }
  
  // Release knob
  if(setCoords(PRM_ALL_RELEASE, size, kbigw, kbigw + 2 + (nfont->getHeight() / 12))) {
    m_release = new cSmartKnob(size, this, PRM_ALL_RELEASE, DEF_NUM_FRAMES, kbig->getWidth(), kbig,
                               nfont, point, frame);
    frame->addView(m_release);
  }
  
  // Attack amp
  if(setCoords(PRM_ALL_ATTACK_AMP, size, ksmallw, ksmallw + 2 + (nfont->getHeight() / 12))) {
    m_attack_amp = new cSmartKnob(size, this, PRM_ALL_ATTACK_AMP, DEF_NUM_FRAMES,
                                 ksmall->getWidth(), ksmall, nfont, point, frame);
    frame->addView(m_attack_amp);
  }
  
  // Decay amp
  if(setCoords(PRM_ALL_DECAY_AMP, size, ksmallw, ksmallw + 2 + (nfont->getHeight() / 12))) {
    m_decay_amp = new cSmartKnob(size, this, PRM_ALL_DECAY_AMP, DEF_NUM_FRAMES,
                                ksmall->getWidth(), ksmall, nfont, point, frame);
    frame->addView(m_decay_amp);
  }
  
  // Sustain amp
  if(setCoords(PRM_ALL_SUSTAIN_AMP, size, ksmallw, ksmallw + 2 + (nfont->getHeight() / 12))) {
    m_sustain_amp = new cSmartKnob(size, this, PRM_ALL_SUSTAIN_AMP, DEF_NUM_FRAMES,
                                  ksmall->getWidth(), ksmall, nfont, point, frame);
    frame->addView(m_sustain_amp);
  }
  
  // ADSR display
  if(setCoords(TAG_ALL_ADSR, size, 146, 47)) {
    m_adsr = new cADSRDisplay(size, this, TAG_ALL_ADSR, 0);
    frame->addView(m_adsr);
  }
  
  m_sw_switch1 = 0;
  m_sw_switch2 = 0;
  switch1();
  switch2();
  updateDisplay();
  
  // m_logger->logS(1030);
  
  setCoords(TAG_HELP_SPLASH, size, 15, 15);
  CRect wsize(0, 0, m_background->getWidth(), m_background->getHeight());
  CBitmap *help = new CBitmap(REZ_HELP_SPLASH);
  m_help = new CSplashScreen(size, this, TAG_HELP_SPLASH, help, wsize, point);
  frame->addView(m_help);
  
  setCoords(TAG_ABOUT_SPLASH, size, 15, 15);
  CBitmap *about = new CBitmap(REZ_ABOUT_SPLASH);
  m_about = new cSplashScreenVersion(size, this, TAG_ABOUT_SPLASH, about, wsize);
  frame->addView(m_about);

  // End of GUI ///////////////////////////////////////////////////////////////////////////
  // m_logger->logS(1031);
  
  btn->forget();
  kbig->forget();
  ksmall->forget();
  vhandle->forget();
  meterhandle->forget();
  fxknob->forget();
  bfont->forget();
  nfont->forget();
  
  this->frame = frame;  
  m_opened = true;
  // m_logger->logS(1032);

  updateDisplay();
  
  updateDisplay();
  
  return true;
}