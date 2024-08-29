/*
537 USB Disk Manager
Version 1.0 Beta

dpi.cpp

Copyright (C) 537 Studio. 2024. All rights reserved.
*/
#include <windows.h>
double dpi=1.0;
void GetDPI(){
    HWND hd=GetDesktopWindow();
    HDC hdc=GetDC(NULL);
	RECT rect;
	GetClientRect(hd,&rect);
	int cw1=(rect.right-rect.left),cw2=GetDeviceCaps(hdc,DESKTOPHORZRES);
	//cw2��ȡ��ʾ��ʵ�ʷֱ��ʣ�cw1��ȡ���ź�ķֱ���
	//��4K 150%�����£�ʵ�ʷֱ���Ϊ3840x2160�����ź�ķֱ���Ϊ2560x1440
    dpi=1.0*cw2/cw1;
	//��ʱ��ȡ��dpiֵΪ1.5
}
void EnableHighDPI(){
    HWND hd=GetDesktopWindow();
    HDC hdc=GetDC(NULL);
	RECT rect;
	GetClientRect(hd,&rect);
	int cw1=(rect.right-rect.left),cw2=GetDeviceCaps(hdc,DESKTOPHORZRES);
    dpi=1.0*cw2/cw1;
    HINSTANCE hUser32=LoadLibrary("User32.dll");
    if(hUser32){
        typedef BOOL (WINAPI* LPSetProcessDPIAware)(void);
        LPSetProcessDPIAware pSetProcessDPIAware=(LPSetProcessDPIAware)GetProcAddress(hUser32,"SetProcessDPIAware");
        if(pSetProcessDPIAware)pSetProcessDPIAware();
        FreeLibrary(hUser32);
    }
}
