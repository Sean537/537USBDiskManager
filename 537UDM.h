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

struct screenSize{
	int width;
	int height;
}scr;

struct WindowInfo{
	HWND hwnd;//窗口句柄 
	HINSTANCE hinstance;//主进程实例句柄
	HDC hdc;//图形设备上下文句柄
}mainwindow;

