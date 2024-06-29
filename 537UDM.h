/*
537 USB Disk Manager
Version 1.0 Beta

537UDM.h

Copyright(C)537 Studio.2024.All rights reserved.
*/

#define APP_NAME_L "537 USB Disk Manager"
#define APP_NAME_S "537UDM"

#define APP_VERSION 1.0

#define APP_DEVELOPER "537 Studio"

#define WINDOW_MAIN_SIZE_WIDTH 400
#define WINDOW_MAIN_SIZE_HEIGHT 600

#ifdef _DEBUG
	#define SHOW_CONSOLE
	#define cmdwindow if(init_console()==TRUE) \
							cmd=1
#else
	#define cmdwindow cmd=0
#endif

bool cmd=0;//0：无命令行窗口	1：有命令行窗口 
