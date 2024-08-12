#include <windows.h>
#include <iostream>
#include <cstring>
#include <string>
#include "ege.h"

#define INFO_FILE 0
#define INFO_IMAGE 1
#define INFO_MEDIA 2

void get_system_info_failed(){
	MessageBox(getHWnd(),"Failed to obtain the necessary system information.\n\nPlease check your system environment or contact 537 Studio for assistance.","Get necessary system info failed.",MB_OK+16);
	exit(-1);
}

void file_lost(int FILETYPE,char filename[]){
	char content[MAX_PATH]="Wrong info: ";
	char addcontent[]=" loaded failed. \n\nPlease reinstall the 537 USB Disk Manager or contact a professional for help from the relevant personnel of 537 Studio.";
	
	strcat(content,filename);
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
