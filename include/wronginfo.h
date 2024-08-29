/*
537 USB Disk Manager
Version 1.0 Beta

wronginfo.h

Copyright (C) 537 Studio. 2024. All rights reserved.
*/
#ifndef _FTSUDM_WRONGINFO_H_
#define _FTSUDM_WRONGINFO_H_

#define INFO_FILE 0
#define INFO_IMAGE 1
#define INFO_MEDIA 2

#include <string>
void get_system_info_failed();
void file_lost(int FILETYPE,std::string filename);

#endif
