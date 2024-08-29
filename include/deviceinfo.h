/*
537 USB Disk Manager
Version 1.0 Beta

deviceinfo.h

Copyright (C) 537 Studio. 2024. All rights reserved.
*/
#ifndef _FTSUDM_DEVICEINFO_H_
#define _FTSUDM_DEVICEINFO_H_

#include <windows.h>

void ConvertSizeToString(ULONGLONG size,char* buffer,size_t bufferSize);
int GetDeviceInfo();

#endif 

#ifndef _FTSUDM_DRIVEINFO_
#define _FTSUDM_DRIVEINFO_
extern char DriveLetter[3];
extern char VolumeName[MAX_PATH];  
extern char FileSystemName[MAX_PATH];  
extern char TotalSpaceStr[256];
extern char FreeSpaceStr[256]; 
#endif


