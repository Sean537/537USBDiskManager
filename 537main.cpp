/*
537 USB Disk Manager
Version 1.0 Beta

537main.cpp

Copyright(C)537 Studio.2024.All rights reserved.
*/

//EGE库API文档：https://xege.org/manual/api/index.htm

#include <iostream>
#include <string> 
#include <sstream>  
#include <windows.h> 
#include <shellapi.h> 
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
using namespace std;

// 辅助函数，用于将ULLONG转换为更易读的格式  
void ConvertSizeToString(ULONGLONG size, char* buffer, size_t bufferSize){  
    if(size<1024){
        snprintf(buffer,bufferSize,"%llu B",size);  
    }else if(size<(1024*1024)){  
        snprintf(buffer,bufferSize,"%.2f KB",static_cast<double>(size)/1024.0);  
    }else if(size<(1024*1024*1024)){  
        snprintf(buffer,bufferSize,"%.2f MB",static_cast<double>(size)/(1024.0*1024.0));  
    }else{  
        snprintf(buffer,bufferSize,"%.2f GB",static_cast<double>(size)/(1024.0*1024.0*1024.0));  
    }  
    buffer[bufferSize-1]='\0'; // 确保字符串以null结尾  
}  
  
int GetDeviceInfo() {  
    char modulePath[MAX_PATH]={0};  
    char driveRoot[3]={0};  
  
    // 获取当前可执行文件的完整路径  
    if(GetModuleFileNameA(NULL,modulePath,MAX_PATH)==0){ 
        cout<<"GetModuleFileNameA failed!"<<endl;  
        return 1;
    } 
  	
    // 从完整路径中提取盘符  
    driveRoot[0]=toupper(modulePath[0]);  
    driveRoot[1]=':';
    driveRoot[2]='/';
    driveRoot[3]='\0';  
  
    // 将盘符复制到全局变量中  
    strncpy(DriveLetter, driveRoot, 4);  
    DriveLetter[2] = '\0'; // 确保DriveLetter以null结尾  
  
    // 获取卷信息  
    if (!GetVolumeInformationA(driveRoot,VolumeName,MAX_PATH,NULL,NULL,NULL,FileSystemName,MAX_PATH)) {  
        cout<<"GetVolumeInformationA failed!"<<endl;  
        return 2;  
    }  
  
    // 获取磁盘空间信息  
    ULARGE_INTEGER totalSpace, freeSpace, totalFreeSpace;  
    if (!GetDiskFreeSpaceExA(driveRoot, &freeSpace, &totalSpace, &totalFreeSpace)) {  
        cout<<"GetDiskFreeSpaceExA failed!"<<endl;  
        return 3;  
    }  
  
    // 转换空间大小为更易读的格式  
    ConvertSizeToString(totalSpace.QuadPart, TotalSpaceStr, sizeof(TotalSpaceStr));  
    ConvertSizeToString(freeSpace.QuadPart, FreeSpaceStr, sizeof(FreeSpaceStr));  
  
    // 输出结果  
    cout<<"DriveLetter: "<<DriveLetter<<endl;  
    cout<<"VolumeName: "<<VolumeName<<endl;  
    cout<<"FileSystemName: "<<FileSystemName<<endl;  
    cout<<"TotalSpace: "<<TotalSpaceStr<<endl;  
    cout<<"FreeSpace: "<<FreeSpaceStr<<endl<<endl;  
    
	return 0;
}

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
	outtextxy(110,15,DriveLetter);
	outtextxy(110,35,VolumeName);
	outtextxy(110,55,FileSystemName);
	char space[MAX_PATH]={};
	strcpy(space,FreeSpaceStr);
	strcat(space," / ");
	strcat(space,TotalSpaceStr);
	outtextxy(110,75,space);
	
	ege_fillrect(0,200,400,200); 
	putimage_withalpha(NULL,FTSLOGO,75,250,100,100,0,0,743,743);
	Sleep(1000);
	for(int i=0;i<=100;i++){
		setfillcolor(EGERGBA(0,122,255,i));
		ege_fillrect(0,200,400,200);
		Sleep(20);
	}
	
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
