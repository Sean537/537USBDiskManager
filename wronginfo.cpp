/*
537 USB Disk Manager
Version 1.0 Beta

wronginfo.cpp

Copyright (C) 537 Studio. 2024. All rights reserved.
*/
#include "include/wronginfo.h"
#include <windows.h>
#include <iostream>
#include <cstring>
#include <string>
#include <cwchar>

#include "include/graphics.h"


void get_system_info_failed(){
	std::wcout<<L"Show \"get system info failed\" MessageBoxW\n";
	MessageBoxW(getHWnd(),L"Failed to obtain the necessary system information.\n\nPlease check your system environment or contact 537 Studio for assistance.",L"Get necessary system info failed.",MB_OK+16);
	exit(-1);
}

void file_lost(int FILETYPE,std::wstring filename){
	std::wcout<<L"Show \"file load failed\" MessageBoxW\n";
	wchar_t content[MAX_PATH]=L"Wrong info: ";
	wchar_t addcontent[]=L" loaded failed. \n\nPlease reinstall the 537 USB Disk Manager or contact a professional for help from the relevant personnel of 537 Studio.";
	
	wchar_t filename_c[filename.length()];
	wcscpy(filename_c,filename.data());
	wcscat(content,filename_c);
	wcscat(content,addcontent);
	
	switch(FILETYPE){
		case INFO_IMAGE:
			MessageBoxW(getHWnd(),content,L"Load the image file failed.",MB_OK+16);
			exit(-1);
			break;
		case INFO_MEDIA:
			MessageBoxW(getHWnd(),content,L"Load the media file failed.",MB_OK+16);
			exit(-1);
			break;
		default:
			MessageBoxW(getHWnd(),content,L"Load the file failed.",MB_OK+16);
			exit(-1);
			break;
	}
}
