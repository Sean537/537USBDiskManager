#include <windows.h>
#include <iostream>
#include <cstring>
#include <string>
#include "ege.h"

#define INFO_FILE 0
#define INFO_IMAGE 1
#define INFO_MEDIA 2

void file_lost(int FILETYPE,char filename[],char filelocation[]){
	char content[MAX_PATH]="Wrong info: ";
	char addcontent_I[]=" loaded failed.\nFile involved: ";
	char addcontent_II[]="\n\nPlease reinstall the 537 USB Disk Manager or contact a professional for help from the relevant personnel of 537 Studio.";
	strcat(content,filename);
	strcat(content,addcontent_I);
	strcat(content,filelocation);
	strcat(content,addcontent_II);
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
