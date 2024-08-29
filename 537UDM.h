/*
537 USB Disk Manager
Version 1.0 Beta

537UDM.h

Copyright (C) 537 Studio. 2024. All rights reserved.
*/

#define APP_NAME_L "537 USB Disk Manager"
#define APP_NAME_S "537UDM"
#define APP_NAME_CN "537U�̹�����"

#define APP_VERSION "1.0 Beta" 
#define APP_BUILDVERSION "2024.8.12.0"

#define APP_DEVELOPER "537 Studio"
#define APP_DEVELOPER_CN "537������"

#define WINDOW_MAIN_SIZE_WIDTH 400
#define WINDOW_MAIN_SIZE_HEIGHT 600

struct screenSize{
	int width;
	int height;
}scr;

struct WindowInfo{
	HWND hwnd;//���ھ�� 
	HINSTANCE hinstance;//������ʵ�����
	HDC hdc;//ͼ���豸�����ľ��
	RECT rect;//���ھ���
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

