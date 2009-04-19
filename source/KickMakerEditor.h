/*
 *  KickMaker - KickMakerEditor.h
 *  Created by Nik Reiman on 03.02.06
 *  Copyright (c) 2006 Teragon Audio, All rights reserved
 */

#ifndef __KickMakerEditor_H
#define __KickMakerEditor_H

#ifndef __cADSRDisplay_H
#include "cADSRDisplay.h"
#endif

#ifndef __cBitmapFont_H
#include "cBitmapFont.h"
#endif

#ifndef __cOptionMenuHidden_H
#include "cOptionMenuHidden.h"
#endif

#ifndef __cTextEditLockable_H
#include "cTextEditLockable.h"
#endif

#ifndef __cKeyedOptionMenu_H
#include "cKeyedOptionMenu.h"
#endif

#ifndef __cLevelDisplayBitmap_H
#include "cLevelDisplayBitmap.h"
#endif

#ifndef __cSmartKnob_H
#include "cSmartKnob.h"
#endif

#ifndef __cSplashScreen_H
#include "cSplashScreen.h"
#endif

#ifndef __cSplashScreenVersion_H
#include "cSplashScreenVersion.h"
#endif

#ifndef __pluginCore_H
#include "pluginCore.h"
#endif

#ifndef __eventManager_H
#include "eventManager.h"
#endif

#ifndef __KickMakerCore_H
#include "KickMakerCore.h"
#endif

#ifndef __fxSelectWave_H
#include "Waveforms/fxSelectWave.h"
#endif

#ifndef __coords_H
#include "coords.h"
#endif

#ifndef __vstgui__
#include "vstgui.h"
#endif

#ifndef __vstcontrols__
#include "vstcontrols.h"
#endif

#ifdef USE_PC_AU
#include <Carbon/Carbon.h>
#include "AUCarbonViewBase.h"
#endif

#include <vector>
#include <string>

class KickMakerEditor : public AEffGUIEditor, public CControlListener {
  public:
#if PLUGGUI
    KickMakerEditor(void *effect);
#else
    KickMakerEditor(AudioEffect *effect);
#endif
    ~KickMakerEditor();
    
#if USE_PC_VST
    virtual void beginEdit(VstInt32 index);
    virtual void endEdit(VstInt32 index);
#endif
    
    virtual bool open(void *ptr);
    virtual void close();
    virtual void idle();
    
    void* getWindow() const;
    
#if USE_PC_AU
    void setAU(AudioUnit unit);
#endif
    bool setCoords(int tag, CRect &size, int width, int height) const;
    void setCore(pluginCore *p);
#if PLUGGUI
    virtual void setParameter(long index, float value);
#else
    virtual void setParameter(VstInt32 index, float value);
#endif
    void updateControl(int tag);
    virtual void valueChanged(CDrawContext* pContext, CControl* pControl);
    
  protected:
      
  private:
    void addMenuOptions(cKeyedOptionMenu *menu);
    void menuOptionHandler(cLevelDisplayBitmap *level, int param);
    void fillPresetMenu(cOptionMenuHidden *menu);
    void switch1();
    void switch2();
    void updateDisplay();
    
    eventManager m_events;
    std::vector<struct tCoords> m_coordmap;
    void *m_window;
    
    CSplashScreen *m_help;
    cSplashScreenVersion *m_about;
    
    cBitmapFont *m_preset_label;
    cOptionMenuHidden *m_preset_menu;
    
    CBitmap *m_background;
    cTextEditLockable *m_preset_edit;
    CKickButton *m_next_button;
    CKickButton *m_prev_button;
    CKickButton *m_save_button;
    CKickButton *m_delete_button;
    
    cKeyedOptionMenu *m_effect_label1_1;
    CHorizontalSlider *m_effect_meter1_1;
    cLevelDisplayBitmap *m_effect_meter_vu1_1;
    cKeyedOptionMenu *m_effect_label1_2;
    CHorizontalSlider *m_effect_meter1_2;
    cLevelDisplayBitmap *m_effect_meter_vu1_2;
    cKeyedOptionMenu *m_effect_label1_3;
    CHorizontalSlider *m_effect_meter1_3;
    cLevelDisplayBitmap *m_effect_meter_vu1_3;
    
    CAnimKnob *m_effect_knob1_1;
    CAnimKnob *m_effect_knob1_2;
    CAnimKnob *m_effect_knob1_3;
    CAnimKnob *m_effect_knob2_1;
    CAnimKnob *m_effect_knob2_2;
    CAnimKnob *m_effect_knob2_3;
    
    cSmartKnob *m_freq1;
    cSmartKnob *m_freq_fine1;
    cSmartKnob *m_attack1;
    cSmartKnob *m_attack_amp1;
    cSmartKnob *m_decay1;
    cSmartKnob *m_decay_amp1;
    cSmartKnob *m_sustain1;
    cSmartKnob *m_sustain_amp1;
    cSmartKnob *m_release1;
    COnOffButton *m_enabled1;
    COnOffButton *m_switch1;
    cADSRDisplay *m_adsr1;
    
    cKeyedOptionMenu *m_effect_label2_1;
    CHorizontalSlider *m_effect_meter2_1;
    cLevelDisplayBitmap *m_effect_meter_vu2_1;
    cKeyedOptionMenu *m_effect_label2_2;
    CHorizontalSlider *m_effect_meter2_2;
    cLevelDisplayBitmap *m_effect_meter_vu2_2;
    cKeyedOptionMenu *m_effect_label2_3;
    CHorizontalSlider *m_effect_meter2_3;
    cLevelDisplayBitmap *m_effect_meter_vu2_3;
    cSmartKnob *m_freq2;
    cSmartKnob *m_freq_fine2;
    cSmartKnob *m_attack2;
    cSmartKnob *m_attack_amp2;
    cSmartKnob *m_decay2;
    cSmartKnob *m_decay_amp2;
    cSmartKnob *m_sustain2;
    cSmartKnob *m_sustain_amp2;
    cSmartKnob *m_release2;
    COnOffButton *m_enabled2;
    COnOffButton *m_switch2;
    cADSRDisplay *m_adsr2;
    
    CVerticalSlider *m_volume1;
    CVerticalSlider *m_volume2;
    CVerticalSlider *m_volume3;
    CVerticalSlider *m_volume4;

    cSmartKnob *m_attack;
    cSmartKnob *m_attack_amp;
    cSmartKnob *m_decay;
    cSmartKnob *m_decay_amp;
    cSmartKnob *m_sustain;
    cSmartKnob *m_sustain_amp;
    cSmartKnob *m_release;
    cADSRDisplay *m_adsr;
    CVerticalSlider *m_volume;
    
    pluginCore *core;
#if USE_PC_AU
    AudioUnit au;
#endif
    
    bool m_opened;
    
    int m_effect1_1, m_effect1_2, m_effect1_3;
    int m_effect2_1, m_effect2_2, m_effect2_3;
    int m_sw_enabled1, m_sw_enabled2, m_sw_switch1, m_sw_switch2;
    int m_sw_freq1, m_sw_freq_fine1, m_sw_attack1, m_sw_decay1, m_sw_sustain1, m_sw_release1;
    int m_sw_attack_amp1, m_sw_decay_amp1, m_sw_sustain_amp1;
    int m_sw_freq2, m_sw_freq_fine2, m_sw_attack2, m_sw_decay2, m_sw_sustain2, m_sw_release2;
    int m_sw_attack_amp2, m_sw_decay_amp2, m_sw_sustain_amp2;
};

#ifdef USE_PC_AU
class KickMakerView : public AUCarbonViewBase {
  public:
    KickMakerView(AudioUnitCarbonView auv);  
    virtual ~KickMakerView();
    
    void RespondToEventTimer(EventLoopTimerRef inTimer);
    virtual OSStatus CreateUI(Float32 xoffset, Float32 yoffset);
    
    Float32 xOffset;
    Float32 yOffset;
  protected:
      KickMakerEditor *editor;
    
  private:
};
#endif

#endif