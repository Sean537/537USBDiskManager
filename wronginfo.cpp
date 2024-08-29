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

#include "include/graphics.h"


void get_system_info_failed(){
	std::cout<<"Show \"get system info failed\" messagebox\n";
	MessageBox(getHWnd(),"Failed to obtain the necessary system information.\n\nPlease check your system environment or contact 537 Studio for assistance.","Get necessary system info failed.",MB_OK+16);
	exit(-1);
}

void file_lost(int FILETYPE,std::string filename){
	std::cout<<"Show \"file load failed\" messagebox\n";
	char content[MAX_PATH]="Wrong info: ";
	char addcontent[]=" loaded failed. \n\nPlease reinstall the 537 USB Disk Manager or contact a professional for help from the relevant personnel of 537 Studio.";
	
	char filename_c[filename.length()];
	strcpy(filename_c,filename.data());
	strcat(content,filename_c);
	strcat(content,addcontent);
	
	switch(FILETYPE){
		case INFO_IMAGE:
			MessageBox(getHWnd(),content,"Load the image file failed.",MB_OK+16);
			exit(-1);
			break;
		case INFO_MEDIA:
			MessageBox(getHWnd(),content,"Load the media file failed.",MB_OK+16);
			exit(-1);
			break;
		default:
			MessageBox(getHWnd(),content,"Load the file failed.",MB_OK+16);
			exit(-1);
			break;
	}
}
