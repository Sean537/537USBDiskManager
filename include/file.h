/*
537 USB Disk Manager
Version 1.0 Beta

file.h

Copyright (C) 537 Studio. 2024. All rights reserved.
*/
#ifndef _FTSUDM_FILE_H_
#define _FTSUDM_FILE_H_

#include <iostream>
#include <string>
#include <vector>

bool IsExeFile(const std::wstring& fileName);
void ScanDirectoryForExe(const std::wstring& directoryPath,std::vector<std::wstring>& exeFiles);
#endif
