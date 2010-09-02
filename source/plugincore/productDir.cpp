/*
 *  productDir.cpp - pluginCore
 *
 *  Created by Nik Reiman on 23.12.05.
 *  Copyright 2005 Teragon Audio. All rights reserved.
 *
 *  This source code may NOT be redistributed without express permission of Teragon Audio.  It may be used
 *  in free or commercial software works, but unauthorized duplication or resale in whole or part is
 *  strictly prohibited.
 */

#ifndef __productDir_H
#include "productDir.h"
#endif

bool getDesktopDir(char *dest)
{
  /** Algorithm: */
#if MAC
  snprintf(dest, MAX_DIR, "%s/Desktop/", getenv("HOME"));
#elif WIN32
  HKEY key;
  DWORD max = MAX_DIR;
  
  if(RegOpenKeyEx(HKEY_CURRENT_USER,
                  "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders",
                  0, KEY_READ, &key) == ERROR_SUCCESS)
  {
    /** \todo Verify this registry key! */
    if(RegQueryValueEx(key, "Desktop", NULL, NULL,
                       (LPBYTE)dest, &max) != ERROR_SUCCESS)
    {
      return false;
    }
    else
    {
      strcat(dest, "\\");
    }
  }
#endif
  return true;  
}

bool getPluginBundleDir(const char *identifier, char *dest)
{
  if(identifier == NULL)
    return false;
  
#if MAC
  CFStringRef id = CFStringCreateWithCString(NULL, identifier, 0);
  if(id == NULL)
    return false;
  
  CFBundleRef br = CFBundleGetBundleWithIdentifier(id);
  if(br == NULL)
    return false;
  
  CFURLRef url = CFBundleCopyBundleURL(br);
  if(url == NULL)
    return false;
  
  CFStringRef cs = CFURLCopyFileSystemPath(url, kCFURLPOSIXPathStyle);  
  if(cs == NULL)
    return false;
  
  if(CFStringGetCString(cs, dest, MAX_DIR, 0) == false)
    return false;
#endif

  return true;
}

bool getProductDir(const char *product, char *dest)
{
  /** Algorithm: */
  char dir[MAX_DIR];

#if MAC
  /** Check for prefs dir, create if not found. */
  snprintf(dir, MAX_DIR, "%s/Library/Application Support/%s/%s",
           getenv("HOME"), ORG_NAME_FULL, product);
  DIR *dp = opendir(dir);
  if(dp == NULL)
  {
    if(mkdir(dir, 0) == -1) {
      /** If no directory exists for the organization, then create one. */
      char tmp[MAX_DIR];
      snprintf(tmp, MAX_DIR, "%s/Library/Application Support/%s", getenv("HOME"), ORG_NAME_FULL);
      if(mkdir(tmp, 0) == -1)
        return false;
      else
        chmod(tmp, S_IRWXU | S_IRWXG | S_IROTH);
    }
    else
    {
      chmod(dir, S_IRWXU | S_IRWXG | S_IROTH);
    }
    return false;
  }
  else
  {
    closedir(dp);
  }
  
  snprintf(dest, MAX_DIR, "%s/Library/Application Support/%s/%s/",
           getenv("HOME"), ORG_NAME_FULL, product);
#elif WIN32
  HKEY key;
  DWORD max = MAX_DIR;
  
  if(RegOpenKeyEx(HKEY_CURRENT_USER,
                  "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders",
                  0, KEY_READ, &key) == ERROR_SUCCESS)
  {
    if(RegQueryValueEx(key, "AppData", NULL, NULL,
                       (LPBYTE)dir, &max) == ERROR_SUCCESS)
    {
      char orgdir[MAX_DIR];
      HANDLE hlist;
      WIN32_FIND_DATA filedata;
      
      sprintf(orgdir, "%s\\%s\\*", dir, ORG_NAME_FULL);
      hlist = FindFirstFile(orgdir, &filedata);
      if(hlist == INVALID_HANDLE_VALUE)
      {
        char tmp[MAX_DIR];
        sprintf(tmp, "%s\\%s", dir, ORG_NAME_FULL);
        if(!CreateDirectory(tmp, NULL))
        {
          return false;
        }
      }
      
      char s_product[MAX_DIR];
      sprintf(s_product, "%s\\%s\\%s\\*", dir, ORG_NAME_FULL, product);
      hlist = FindFirstFile(s_product, &filedata);
      if(hlist == INVALID_HANDLE_VALUE)
      {
        char tmp[MAX_DIR];
        sprintf(tmp, "%s\\%s\\%s", dir, ORG_NAME_FULL, product);
        if(!CreateDirectory(tmp, NULL))
        {
          return false;
        }
      }
      
      FindClose(hlist);
      RegCloseKey(key);
      
      _snprintf(dest, MAX_DIR, "%s\\%s\\%s\\", dir, ORG_NAME_FULL, product);
    }
  }
#endif
  
  // If we made it this far, then we're good to go
  return true;
}
