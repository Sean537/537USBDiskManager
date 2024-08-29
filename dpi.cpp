/*
537 USB Disk Manager
Version 1.0 Beta

dpi.cpp

Copyright (C) 537 Studio. 2024. All rights reserved.
*/
#include <windows.h>
#include <iostream>
double dpi=1.0;
void GetDPI(){
	std::cout<<"Get DPI: ";
    HWND hd=GetDesktopWindow();
    HDC hdc=GetDC(NULL);
	RECT rect;
	GetClientRect(hd,&rect);
	int cw1=(rect.right-rect.left),cw2=GetDeviceCaps(hdc,DESKTOPHORZRES);
	//cw2获取显示器实际分辨率，cw1获取缩放后的分辨率
	//如4K 150%缩放下，实际分辨率为3840x2160，缩放后的分辨率为2560x1440
    dpi=1.0*cw2/cw1;
	//此时获取的dpi值为1.5
	std::cout<<dpi<<std::endl;
}
void EnableHighDPI(){
    HWND hd=GetDesktopWindow();
    HDC hdc=GetDC(NULL);
	RECT rect;
	GetClientRect(hd,&rect);
	int cw1=(rect.right-rect.left),cw2=GetDeviceCaps(hdc,DESKTOPHORZRES);
    dpi=1.0*cw2/cw1;
    std::cout<<"Enable high DPI: "<<dpi<<std::endl;
    HINSTANCE hUser32=LoadLibrary("User32.dll");
    if(hUser32){
    	std::cout<<"Use User32.dll successful.\n\n";
        typedef BOOL (WINAPI* LPSetProcessDPIAware)(void);
        LPSetProcessDPIAware pSetProcessDPIAware=(LPSetProcessDPIAware)GetProcAddress(hUser32,"SetProcessDPIAware");
        if(pSetProcessDPIAware)pSetProcessDPIAware();
        FreeLibrary(hUser32);
    }else{
    	std::cout<<"Use User32.dll failed.\n\n";
	}
}
