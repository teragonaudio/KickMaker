#define MAC 1
#define MACX 1
#define QUARTZ 1
#define TARGET_API_MAC_CARBON 1
#define VST_FORCE_DEPRECATED 0
#define USENAVSERVICES 1

#define USE_PC_APP 1
#define USE_PC_MIDI 1
#define USE_PC_HOST 1
#define USE_PC_VST 1

#define __CF_USE_FRAMEWORK_INCLUDES__

#if __MWERKS__
#define __NOEXTENSIONS__
#endif

#define MAC_OS_X_VERSION_MIN_REQUIRED   1020
#define MAC_OS_X_VERSION_MAX_ALLOWED	1030
#define DEF_PRODUCT "KickMaker"
#define DEF_BUNDLE_STRING "org.teragon.KickMaker.app"

#include <Carbon/Carbon.h>
#include <AvailabilityMacros.h>