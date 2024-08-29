/*
537 USB Disk Manager
Version 1.0 Beta

537main.cpp

Copyright(C)537 Studio.2024.All rights reserved.
*/

//EGE库API文档：https://xege.org/manual/api/index.htm


#include "include/graphics.h" 
#include "537UDM.h"
#include "include/main_window.h"
#include "include/wronginfo.h"  

#ifdef DEBUG
	#define ShowConsoleWindow AllocConsole();	\
							freopen("CONOUT$", "w", stdout);	\
							SetConsoleTitle("537UDM - Debug");
	#define getch getch();
#else
	#define ShowConsoleWindow
	#define getch
#endif




int main(){
	ShowConsoleWindow;
	if(GetDeviceInfo()!=0){
		get_system_info_failed();
	}
	
	// 获取屏幕宽度和高度  
    scr.width = GetSystemMetrics(SM_CXSCREEN);  
    scr.height = GetSystemMetrics(SM_CYSCREEN);  
    cout<<"Get screen width: "<<scr.width<<"px\n";
    cout<<"Get screen height: "<<scr.height<<"px\n\n";
    
	initgraph(WINDOW_MAIN_SIZE_WIDTH,WINDOW_MAIN_SIZE_HEIGHT,0);//创建窗口  
	cout<<"Create window\n";
	
	setcaption(APP_NAME_L);//设置窗口标题
	cout<<"Set window title: "<<APP_NAME_L<<"\n";
	movewindow(scr.width-WINDOW_MAIN_SIZE_WIDTH+5,scr.height-WINDOW_MAIN_SIZE_HEIGHT-30);//设置窗口显示在屏幕右下角 
    cout<<"Move window to: "<<scr.width-WINDOW_MAIN_SIZE_WIDTH+5<<", "<<scr.height-WINDOW_MAIN_SIZE_HEIGHT-30<<"\n";
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
    cout<<"Set color: "<<255<<", "<<255<<", "<<255<<", "<<100<<"\n\n";
    
	PIMAGE FTSLOGO=newimage();
	if(getimage(FTSLOGO,"./resource/537logo.png")!=grOk){
    	//读取图片文件失败
    	cout<<"Load FTSLOGO failed.\n";
    	file_lost(INFO_IMAGE,"FTSLOGO");
	}else{
		cout<<"Load FTSLOGO successed.\n";
	}
	putimage(5,5,100,100,FTSLOGO,0,0,743,743);
	cout<<"Put FTSLOGO to: "<<"x="<<5<<" y="<<5<<" width="<<100<<" height="<<100<<"\n";
	outtextxy(110,15,DriveLetter);
	outtextxy(110,35,VolumeName);
	outtextxy(110,55,FileSystemName);
	char space[MAX_PATH]={};
	strcpy(space,FreeSpaceStr);
	strcat(space," / ");
	strcat(space,TotalSpaceStr);
	outtextxy(110,75,space);
	//outtextrect(110,50,200,30,"This is a test. Just show the ege text out.");
	
	delimage(FTSLOGO); 
	
    /*
	setbkcolor();//背景色 
    setbkcolor_f();//清屏背景色
	setfillcolor();//填充色
	setfontbkcolor();//文本背景色
	
	ege_setalpha();//设置统一透明度 
    */
	getch;//等待用户输入 

    closegraph();//关闭绘图窗口 
    return 0;
}
