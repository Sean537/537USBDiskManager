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
#include "include/graphics.h" 
#include "537UDM.h"
#include "include/main_window.h"
#include "include/wronginfo.h"  

int GetDeviceInfo();
void ConvertSizeToString(ULONGLONG size, char* buffer, size_t bufferSize);

int main(){
	// 获取屏幕宽度和高度  
    scr.width = GetSystemMetrics(SM_CXSCREEN);  
    scr.height = GetSystemMetrics(SM_CYSCREEN);  
    
	initgraph(WINDOW_MAIN_SIZE_WIDTH,WINDOW_MAIN_SIZE_HEIGHT,0);//创建窗口  
	movewindow(scr.width-WINDOW_MAIN_SIZE_WIDTH,scr.height-WINDOW_MAIN_SIZE_HEIGHT);//设置窗口显示在屏幕右下角 
    setrendermode(RENDER_MANUAL);//设置手动渲染模式，需要调用delay_fps()/delay_ms()等函数时才会更新窗口，可减少闪烁 
	ege_enable_aa(true);//开启窗口抗锯齿 
	
	setcaption(APP_NAME_L);//设置窗口标题
	
	mainwindow.hwnd=getHWnd();//获取主窗口句柄 
	mainwindow.hinstance=getHInstance();//获取主进程实例句柄 
	mainwindow.hdc=getHDC();//获取图形接口设备上下文句柄  
    
    settextjustify(LEFT_TEXT,CENTER_TEXT);//设置文本上下左右居中 
    setbkmode(TRANSPARENT);//设置文本输出带透明背景 
    setcolor(EGERGBA(255,255,255,100));//前景色
    
	PIMAGE FTSLOGO=newimage();
	if (getimage(FTSLOGO,"./resource/537logo.png")!=grOk) {
    	//读取图片文件失败
    	file_lost(INFO_IMAGE,"FTSLOGO","resource/537logo.png");
	}
	putimage(5,5,100,100,FTSLOGO,0,0,743,743);
	
	outtextxy(110,5,DriveLetter);
	outtextxy(110,25,VolumeName);
	outtextxy(110,45,FileSystemName);
	//outtextrect(110,50,200,30,"This is a test. Just show the ege text out.");
	
	delimage(FTSLOGO); 
	
    /*
	setbkcolor();//背景色 
    setbkcolor_f();//清屏背景色
	setfillcolor();//填充色
	setfontbkcolor();//文本背景色
	
	ege_setalpha();//设置统一透明度 
    */
	getch();//等待用户输入 

    closegraph();//关闭绘图窗口 
    return 0;
}

// 辅助函数，用于将ULLONG转换为更易读的格式  
void ConvertSizeToString(ULONGLONG size, char* buffer, size_t bufferSize) {  
    if (size < 1024) {  
        snprintf(buffer, bufferSize, "%llu B", size);  
    } else if (size < (1024 * 1024)) {  
        snprintf(buffer, bufferSize, "%.2f KB", static_cast<double>(size) / 1024.0);  
    } else if (size < (1024 * 1024 * 1024)) {  
        snprintf(buffer, bufferSize, "%.2f MB", static_cast<double>(size) / (1024.0 * 1024.0));  
    } else {  
        snprintf(buffer, bufferSize, "%.2f GB", static_cast<double>(size) / (1024.0 * 1024.0 * 1024.0));  
    }  
    buffer[bufferSize - 1] = '\0'; // 确保字符串以null结尾  
}  
  
int GetDeviceInfo() {  
    char modulePath[MAX_PATH] = {0};  
    char driveRoot[3] = {0};  
  
    // 获取当前模块（可执行文件）的完整路径  
    if (GetModuleFileNameA(NULL, modulePath, MAX_PATH) == 0) {  
        std::cerr << "GetModuleFileNameA failed!" << std::endl;  
        return 2;  
    }  
  
    // 从完整路径中提取盘符  
    driveRoot[0] = toupper(modulePath[0]);  
    driveRoot[1] = ':';  
    driveRoot[2] = '\0';  
  
    // 将盘符复制到全局变量中  
    strncpy(DriveLetter, driveRoot, 3);  
    DriveLetter[3] = '\0'; // 确保DriveLetter以null结尾  
  
    // 获取卷信息  
    if (!GetVolumeInformationA(driveRoot, VolumeName, MAX_PATH, NULL, NULL, NULL, FileSystemName, MAX_PATH)) {  
        std::cerr << "GetVolumeInformationA failed!" << std::endl;  
        return 3;  
    }  
  
    // 获取磁盘空间信息  
    ULARGE_INTEGER totalSpace, freeSpace, totalFreeSpace;  
    if (!GetDiskFreeSpaceExA(driveRoot, &freeSpace, &totalSpace, &totalFreeSpace)) {  
        std::cerr << "GetDiskFreeSpaceExA failed!" << std::endl;  
        return 4;  
    }  
  
    // 转换空间大小为更易读的格式  
    ConvertSizeToString(totalSpace.QuadPart, TotalSpaceStr, sizeof(TotalSpaceStr));  
    ConvertSizeToString(freeSpace.QuadPart, FreeSpaceStr, sizeof(FreeSpaceStr));  
  
    // 输出结果  
    std::cout << "DriveLetter: " << DriveLetter << std::endl;  
    std::cout << "VolumeName: " << VolumeName << std::endl;  
    std::cout << "FileSystemName: " << FileSystemName << std::endl;  
    std::cout << "TotalSpace: " << TotalSpaceStr << std::endl;  
    std::cout << "FreeSpace: " << FreeSpaceStr << std::endl;  
    
	return 1;
}
