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
	//cw2获取显示器实际分辨率，cw1获取缩放后的分辨率
	//如4K 150%缩放下，实际分辨率为3840x2160，缩放后的分辨率为2560x1440
    dpi=1.0*cw2/cw1;
	//此时获取的dpi值为1.5
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
