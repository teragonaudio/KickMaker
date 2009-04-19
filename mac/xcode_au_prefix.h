#define MAC 1
#define MACX 1
#define XML_STATIC 1
#define PLUGGUI 1
#define QUARTZ 1
#define TARGET_API_MAC_CARBON 1
#define USENAVSERVICES 1

#if __ppc__
#define VST_FORCE_DEPRECATED 0
#else
#define VST_FORCE_DEPRECATED 1
#endif

#if __MWERKS__
#define __NOEXTENSIONS__
#endif

#define PluginGUIEditor AEffGUIEditor

#include <Carbon/Carbon.h>
#include <AudioUnit/AudioUnit.h>
#include <AvailabilityMacros.h>
#include "vstgui.h"

#define USE_PC_AU 1

#ifndef __defaults_h__
#include "defaults.h"
#endif