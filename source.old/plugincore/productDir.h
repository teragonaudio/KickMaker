/*
 *  productDir.h - pluginCore
 *
 *  Created by Nik Reiman on 23.12.05.
 *  Copyright 2005 Teragon Audio. All rights reserved.
 *
 *  This source code may NOT be redistributed without express permission of Teragon Audio.  It may be used
 *  in free or commercial software works, but unauthorized duplication or resale in whole or part is
 *  strictly prohibited.
 */

#ifndef __productDir_H
#define __productDir_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#if MAC
#include <sys/stat.h>
#include <dirent.h>
#include <Carbon/Carbon.h>
#endif

#if WINDOWS
#include <Windows.h>
#endif

#ifndef ORG_NAME_FULL
/*! Redefine this macro in your build settings to reflect your organization name. */
#define ORG_NAME_FULL "Teragon Audio"
#endif
#ifndef ORG_NAME_CANONICAL
/** Redefine this macro in your build settings to reflect your organization name. */
#define ORG_NAME_CANONICAL "org.teragon"
#endif

#ifndef MAX_DIR
#define MAX_DIR 512
#endif

/*! \brief Get the path to the user's desktop (used primarily by xmlLogger)
* \param dest Character string to write the result to (should be MAX_DIR characters long)
*/
bool getDesktopDir(char *dest);

/*! \brief Gets the full path to the plugin's bundle root (Mac OSX only)
* \param identifier Bundle identifier (ie, "com.example.yourcompany")
* \param dest A pre-allocated string to which the directory will be stored
* \return True on success, false on error */
bool getPluginBundleDir(const char *identifier, char *dest);

/*! \brief Gets the product's scratch directory, creating it if necessary
* \param product The full product name
* \param dest A pre-allocated string to which the directory will be stored
* \return True on success, false if errors occurred
*
* Returns the product's save directory, which can be used to store logfiles, scratch
* data, and other temporary files.  Under Mac OSX, this will be located at
* "$HOME/Library/Application Support/Organization Name/Product Name/".  Under Windows, it is
* "$HOME\Application Data\Orginization Name\Product Name\".  Note the trailing slashes. */
bool getProductDir(const char *product, char *dest);

#endif