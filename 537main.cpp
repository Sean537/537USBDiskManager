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
#include "include/dpi.h"
#include "include/file.h"
#include "include/netpp.h"
#include "resource.h"

using namespace std;

int main(){
	fShowConsoleWindow;//显示命令行窗口 
	
	if(GetDeviceInfo()!=0){//获取设备信息失败 
		get_system_info_failed();
	}
	
	
	// 获取屏幕宽度和高度  
    scr.width = GetSystemMetrics(SM_CXSCREEN);  
    cout<<"Get screen width: "<<scr.width<<"px\n";
	scr.height = GetSystemMetrics(SM_CYSCREEN);  
    cout<<"Get screen height: "<<scr.height<<"px\n\n";
    
	
	
	taskbar.hwnd=::FindWindow("Shell_TrayWnd","");//获取任务栏hwnd信息 
	cout<<"Get taskbar hwnd: "<<taskbar.hwnd<<"\n";
	::GetWindowRect(taskbar.hwnd,&taskbar.rect);//获取任务栏窗口rect信息 
	cout<<"Get taskbar rect\n";
	taskbar.x=taskbar.rect.left;//计算任务栏窗口x坐标 
	cout<<"Taskbar's x: "<<taskbar.x<<"\n";
	taskbar.y=taskbar.rect.top;//计算任务栏窗口y坐标 
	cout<<"Taskbar's y: "<<taskbar.y<<"\n";
	taskbar.width=taskbar.rect.right-taskbar.rect.left;//计算任务栏窗口宽度 
	cout<<"Taskbar's width: "<<taskbar.width<<"\n";
	taskbar.height=taskbar.rect.bottom-taskbar.rect.top;//计算任务栏窗口高度 
	cout<<"Taskbar's height: "<<taskbar.height<<"\n\n";
	
	mainwindow.width=WINDOW_MAIN_SIZE_WIDTH;//主窗口宽度 
	cout<<"Main window's width: "<<mainwindow.width<<"\n";
	mainwindow.height=WINDOW_MAIN_SIZE_HEIGHT;//主窗口高度 
	cout<<"Main window's height: "<<mainwindow.height<<"\n";
	mainwindow.x=scr.width-mainwindow.width;//主窗口x坐标 
	cout<<"Main window's x: "<<mainwindow.x<<"\n";
	mainwindow.y=scr.height-mainwindow.height-taskbar.height;//主窗口y坐标 
	cout<<"Main window's y: "<<mainwindow.y<<"\n\n";
	
	setcaption(APP_NAME_EN_L);//设置窗口标题
	cout<<"Set window title: "<<APP_NAME_EN_L<<"\n";
	setinitmode(0,mainwindow.x,mainwindow.y);//设置初始化窗口位置在屏幕右下角 
	cout<<"Set window location: "<<mainwindow.x<<", "<<mainwindow.y<<"\n";
	initgraph(WINDOW_MAIN_SIZE_WIDTH*dpi,WINDOW_MAIN_SIZE_HEIGHT*dpi,0);//创建窗口  
	cout<<"Create window\n";
	setrendermode(RENDER_MANUAL);//设置手动渲染模式，需要调用delay_fps()/delay_ms()等函数时才会更新窗口，可减少闪烁 
	cout<<"Set render mode\n";
    ege_enable_aa(true);//开启窗口抗锯齿 
    cout<<"Enable aa\n\n";
	
	GetDPI();//获取系统DPI 
	EnableHighDPI();//尝试启用更高DPI 
	
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
    cout<<"Set color: "<<255<<", "<<255<<", "<<255<<", "<<100<<"\n";
    setfillcolor(EGERGB(1,182,19));
    cout<<"Set fill color: "<<1<<", "<<182<<", "<<19<<"\n\n";
    
	PIMAGE FTSLOGO=newimage();
	if(getimage(FTSLOGO,"./resource/537logo.png")!=grOk){
    	//读取图片文件失败
    	cout<<"Load FTSLOGO failed.\n";
    	file_lost(INFO_IMAGE,"FTSLOGO");
	}else{
		cout<<"Load FTSLOGO successed.\n";
	}
	putimage_withalpha(NULL,FTSLOGO,5,5,100,100,0,0,743,743);
	cout<<"Put FTSLOGO to: "<<"x="<<5<<" y="<<5<<" width="<<100<<" height="<<100<<"\n\n";
	
	outtextxy(110*dpi,15*dpi,DriveLetter);
	cout<<"Output Drive Letter\n";
	outtextxy(110*dpi,35*dpi,VolumeName);
	cout<<"Output Volume Name\n";
	outtextxy(110*dpi,55*dpi,FileSystemName);
	cout<<"Output File System Name\n";
	char space[MAX_PATH]={};
	strcpy(space,FreeSpaceStr);
	strcat(space," / ");
	strcat(space,TotalSpaceStr);
	outtextxy(110,75,space);
	cout<<"Output Drive Letter\n\n";
	delay_ms(20);
	
	ege_fillrect(0*dpi,200*dpi,400*dpi,200*dpi); 
	putimage_withalpha(NULL,FTSLOGO,75,250,100,100,0,0,743,743);
	cout<<"Put FTSLOGO2 to: "<<75<<", "<<250<<"\n\n";
	
	delay_ms(1000);
	cout<<"Paused 1 second\n\n";
	
	for(int i=0;i<=100;i++){
		setfillcolor(EGERGBA(0,122,255,i));
		cout<<"Set fill color: RGBA(0,122,255,"<<i<<")\n";
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
	cout<<"\nCreate editbox\n\n";
	//outtextrect(110,50,200,30,"This is a test. Just show the ege text out.");
	
	delimage(FTSLOGO); 
	
	
	Gif gif(L"resource/loader1.gif");
	cout<<"Load GIF\n";
	gif.setPos(30,150);
	cout<<"Set GIF pos: 30,150\n";
	gif.setSize(48,48);
	cout<<"Set GIF size: 48,48\n";
	gif.info();//控制台输出Gif图像信息
	gif.play();
	cout<<"Draw GIF...\n\n";
	for(int i=0;i<=100;i++,delay_fps(60)) {
		gif.draw();
		
	}
	
	string directoryPath="."; // 表示当前目录
    vector<string> exeFiles;
    // 扫描当前目录及其所有子目录
    cout<<"Scanning EXE files...\n";
	ScanDirectoryForExe(directoryPath, exeFiles);
    // 打印所有找到的.exe文件路径
    for(const auto& file:exeFiles){
        std::cout << file << std::endl;
    }
    /*
	setbkcolor();//背景色 
    setbkcolor_f();//清屏背景色
	setfillcolor();//填充色
	setfontbkcolor();//文本背景色
	
	ege_setalpha();//设置统一透明度 
    */
    /*
    setfillcolor(EGERGB(255,255,255));
    while(true){
    	if (keystate(key_mouse_l)) { // 鼠标左键按下了
    		std::cout<<"鼠标左键按下\n";
			//获取鼠标当前位置坐标，放在变量mouse_x和mouse_y中 
    		int mouse_x,mouse_y;
    		mousepos(&mouse_x,&mouse_y);
    		//在鼠标当前位置画一个半径为100的圆
    		fillcircle(mouse_x,mouse_y,20);
		}

	}
	*/
	
	//NewHttpServe();
	//StartHttpServe(GoString{"https://192.168.1.1:5376",24},256);
	//ReadFromHttpConn(128,GoString{"https://sean537.github.io/index.html",36});
	
	
	fgetch;//等待用户输入 
    closegraph();//关闭绘图窗口 
    return 0;
}
