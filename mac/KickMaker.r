/*
 *  KickMaker - KickMaker.r
 *  Created by Nik Reiman on 05.02.06
 *  Copyright (c) 2006 Teragon Audio, All rights reserved
 */

#include <AudioUnit/AudioUnit.r>

#ifndef __defaults_H
#include "defaults.h"
#endif

// Note that resource IDs must be spaced 2 apart for the 'STR ' name and description
#define kAudioUnitResID_KickMaker 1000
#define kAudioUnitResID_KickMakerView 2000

#define KickMaker_COMP_SUBTYPE 'KkMk'
#define KickMaker_COMP_MANF 'Tera'
#define kKickMakerVersion 0x00010000

//////////////////////////////////////////////////////////////////////////////

#define RES_ID kAudioUnitResID_KickMaker
#define COMP_TYPE kAudioUnitType_MusicDevice
#define COMP_SUBTYPE KickMaker_COMP_SUBTYPE
#define COMP_MANUF KickMaker_COMP_MANF	

#define VERSION kKickMakerVersion
#define NAME "Teragon Audio: KickMaker"
#define DESCRIPTION "KickMaker AU"
#define ENTRY_POINT "KickMakerEntry"

#include "AUResources.r"

//////////////////////////////////////////////////////////////////////////////

#define RES_ID kAudioUnitResID_KickMakerView
#define COMP_TYPE kAudioUnitCarbonViewComponentType
#define COMP_SUBTYPE KickMaker_COMP_SUBTYPE
#define COMP_MANUF KickMaker_COMP_MANF

#define VERSION kKickMakerVersion
#define NAME "Teragon Audio: KickMaker"
#define DESCRIPTION "Kickmaker VSTGUI AUView"
#define ENTRY_POINT "KickMakerViewEntry"

#include "AUResources.r"