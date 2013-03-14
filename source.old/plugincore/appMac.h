/*
 *  appMac.h - pluginCore
 *
 *  Created by Nik Reiman on 12.11.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 *  This source code may NOT be redistributed without express permission of Teragon Audio.  It may be used
 *  in free or commercial software works, but unauthorized duplication or resale in whole or part is
 *  strictly prohibited.
 */

#ifdef USE_PC_APP
#if MAC

#ifndef __appMac_H
#define __appMac_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <vector>

#include "AUCarbonViewBase.h"
#include "AUCarbonViewControl.h"
#include "AUBase.h"
#include "CoreMIDI/MIDIServices.h"

#ifndef __defaults_H
#include "defaults.h"
#endif

#ifndef __productDir_H
#include "productDir.h"
#endif

#ifndef __pluginLoader_H
#include "pluginLoader.h"
#endif

#ifndef __vstLoader_H
#include "vstLoader.h"
#endif

#ifndef __aeffectx__
#include "aeffectx.h"
#endif

#ifndef Expat_INCLUDED
#include "expat.h"
#endif

#define DEF_DELIMITER '/'
#define DEF_RESOURCE_PATH "Contents/Resources"
#define DEF_EXTENSION ".vst"

#ifndef MAX_PATH
#define MAX_PATH 512
#endif

OSStatus process(void *inRefCon, AudioUnitRenderActionFlags *ioActionFlags, 
                 const AudioTimeStamp *inTimeStamp, UInt32 inBusNumber, 
                 UInt32 inNumberFrames, AudioBufferList *ioData);
void processMidi(const MIDIPacketList *pktlist, void *readProcRefCon, void *srcConnRefCon);
void *runEventLoop(void *plug);
void *runPluginLoop(void *plug);
void quit(int signal);

#endif
#endif
#endif