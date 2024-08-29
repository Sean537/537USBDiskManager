/*
537 USB Disk Manager
Version 1.0 Beta

537main.cpp

Copyright (C) 537 Studio. 2024. All rights reserved.
*/

//EGE库API文档：https://xege.org/manual/api/index.htm

#include <iostream>
#include <string> 
#include <sstream>
#include <windows.h> 
#include <shellapi.h> 
#include "537UDM.h"
#include "include/graphics.h"
#include "include/ege/sys_edit.h" 
#include "include/gif.h"
#include "include/wronginfo.h"
#include "include/deviceinfo.h"
using namespace std;

double dpi=1.0;
void GetDPI()
{
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
void EnableHighDPI()
{
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

int main(){
	GetDPI();
	EnableHighDPI();
	fShowConsoleWindow;
	if(GetDeviceInfo()!=0){
		get_system_info_failed();
	}
	
	// 获取屏幕宽度和高度  
    scr.width = GetSystemMetrics(SM_CXSCREEN);  
    scr.height = GetSystemMetrics(SM_CYSCREEN);  
    cout<<"Get screen width: "<<scr.width<<"px\n";
    cout<<"Get screen height: "<<scr.height<<"px\n\n";
    
	initgraph(WINDOW_MAIN_SIZE_WIDTH*dpi,WINDOW_MAIN_SIZE_HEIGHT*dpi,0);//创建窗口  
	cout<<"Create window\n";
	
	taskbar.hwnd=::FindWindow("Shell_TrayWnd","");
	::GetWindowRect(taskbar.hwnd,&taskbar.rect);
	taskbar.x=taskbar.rect.left;
	taskbar.y=taskbar.rect.top;
	taskbar.width=taskbar.rect.right-taskbar.rect.left;
	taskbar.height=taskbar.rect.bottom-taskbar.rect.top;
	
	mainwindow.width=WINDOW_MAIN_SIZE_WIDTH;
	mainwindow.height=WINDOW_MAIN_SIZE_HEIGHT;
	mainwindow.x=scr.width-mainwindow.width;
	mainwindow.y=scr.height-mainwindow.height-taskbar.height;
	
	setcaption(APP_NAME_L);//设置窗口标题
	cout<<"Set window title: "<<APP_NAME_L<<"\n";
	movewindow(mainwindow.x,mainwindow.y);//设置窗口显示在屏幕右下角 
    cout<<"Move window to: "<<mainwindow.x<<", "<<mainwindow.y<<"\n";
	setrendermode(RENDER_MANUAL);//设置手动渲染模式，需要调用delay_fps()/delay_ms()等函数时才会更新窗口，可减少闪烁 
	cout<<"Set render mode\n";
    ege_enable_aa(true);//开启窗口抗锯齿 
    cout<<"Enable aa\n\n";
	
	mainwindow.hwnd=getHWnd();//获取主窗口句柄 
	cout<<"Get HWnd: "<<mainwindow.hwnd<<"\n";
	mainwindow.hinstance=getHInstance();//获取主进程实例句柄
	cout<<"Get HInstance: "<<mainwindow.hinstance<<"\n";
	mainwindow.hdc=getHDC();//获取图形接口设备上下文句柄 
	cout<<"Get HDC: "<<mainwindow.hdc<<"\n\n";
    
    settextjustify(LEFT_TEXT,CENTER_TEXT);//设置文本上下左右居中 
    cout<<"Set text location mode: "<<LEFT_TEXT<<", "<<CENTER_TEXT<<"\n";
    setbkmode(TRANSPARENT);//设置文本输出带透明背景 
    cout<<"Set background mode: "<<TRANSPARENT<<"\n";
    setcolor(EGERGBA(255,255,255,100));//前景色
    setfillcolor(EGERGB(1,182,19));
    cout<<"Set color: "<<255<<", "<<255<<", "<<255<<", "<<100<<"\n\n";
    
	PIMAGE FTSLOGO=newimage();
	if(getimage(FTSLOGO,"./resource/537logo.png")!=grOk){
    	//读取图片文件失败
    	cout<<"Load FTSLOGO failed.\n";
    	file_lost(INFO_IMAGE,"FTSLOGO");
	}else{
		cout<<"Load FTSLOGO successed.\n";
	}
	putimage_withalpha(NULL,FTSLOGO,5,5,100,100,0,0,743,743);
	cout<<"Put FTSLOGO to: "<<"x="<<5<<" y="<<5<<" width="<<100<<" height="<<100<<"\n";
	outtextxy(110*dpi,15*dpi,DriveLetter);
	outtextxy(110*dpi,35*dpi,VolumeName);
	outtextxy(110*dpi,55*dpi,FileSystemName);
	char space[MAX_PATH]={};
	strcpy(space,FreeSpaceStr);
	strcat(space," / ");
	strcat(space,TotalSpaceStr);
	outtextxy(110,75,space);
	
	ege_fillrect(0*dpi,200*dpi,400*dpi,200*dpi); 
	putimage_withalpha(NULL,FTSLOGO,75,250,100,100,0,0,743,743);
	Sleep(1000);
	for(int i=0;i<=100;i++){
		setfillcolor(EGERGBA(0,122,255,i));
		ege_fillrect(0,200,400,200);
		delay_ms(20);
	}
	sys_edit editBox;
	editBox.create(1);						//创建，false表示单行，true表示多行
	editBox.setreadonly(false);		//设置输入框允许输入
	editBox.move(100, 100);						//设置位置
	editBox.size(200,100);	//设置尺寸
	editBox.setmaxlen(20);						//设置允许输入的字符数
	editBox.setfont(20*dpi,8*dpi,"微软雅黑");
	editBox.visible(true);						//设置可见性
	editBox.settext("");
	editBox.setfocus();							//设置获取焦点
	
	//outtextrect(110,50,200,30,"This is a test. Just show the ege text out.");
	
	delimage(FTSLOGO); 
	
	
	Gif gif(L"resource/loader1.gif");
	gif.setPos(30,150);
	gif.setSize(48,48);
	gif.info();//控制台输出Gif图像信息
	gif.play();

	for (; is_run(); delay_fps(60)) {
		gif.draw();
	}
	
	
    /*
	setbkcolor();//背景色 
    setbkcolor_f();//清屏背景色
	setfillcolor();//填充色
	setfontbkcolor();//文本背景色
	
	ege_setalpha();//设置统一透明度 
    */
    while(true){
    	
	}
	fgetch;//等待用户输入 
    closegraph();//关闭绘图窗口 
    return 0;
}
