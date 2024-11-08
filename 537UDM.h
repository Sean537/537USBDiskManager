/*
537 USB Disk Manager
Version 1.0 Beta

537UDM.h

Copyright (C) 537 Studio. 2024. All rights reserved.
*/

#define APP_NAME_EN_L "537 USB Disk Manager"
#define APP_NAME_EN_S "537UDM"
#define APP_NAME_CN "537U盘管理器"

#define APP_VERSION "1.0 Beta" 
#define APP_BUILDVERSION "2024.10.15.0.W10"

#define APP_DEVELOPER_EN "537 Studio"
#define APP_DEVELOPER_CN "537工作室"

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
	RECT rect;//窗口矩形
	int x;
	int y;
	int width;
	int height; 
}mainwindow,taskbar;

#ifdef DEBUG
	#define fShowConsoleWindow AllocConsole();	\
							freopen("CONOUT$", "w", stdout);	\
							SetConsoleTitle("537UDM - Debug");
	#define fgetch getch();
#else
	#define fShowConsoleWindow
	#define fgetch
#endif

