/*
537 USB Disk Manager
Version 1.0 Beta

537main.cpp

Copyright(C)537 Studio.2024.All rights reserved.
*/

//EGE库API文档：https://xege.org/manual/api/index.htm

#include <iostream>
#include <string> 
#include <windows.h>  
#include "include/graphics.h" 
#include "537UDM.h"
#include "include/main_window.h"

std::string DI_driveLetter;//卷标 
std::string DI_volumeName;//卷名称
std::string DI_fileSystemName;//文件系统名称
double DI_totalSize_GB;//总空间（GB）
double DI_freeSize_GB;//剩余空间（GB）  

std::string GetCurrentExecutableDriveLetter() {  
    char buffer[MAX_PATH];  
    GetModuleFileNameA(nullptr, buffer, MAX_PATH);  
    std::string path(buffer);  
    size_t pos = path.find_first_of(":");  
    if (pos != std::string::npos) {  
        return path.substr(0, pos + 1);  
    }  
    return ""; // 没有找到驱动器号  
}  
  
void GetVolumeInfo(const std::string& driveLetter) {  
    char volumeName[MAX_PATH] = "";  
    char fileSystemName[MAX_PATH] = "";  
    DWORD serialNumber = 0;  
    DWORD maxComponentLength = 0;  
    DWORD fileSystemFlags = 0;  
  
    BOOL isReady = GetVolumeInformationA(  
        driveLetter.c_str(),  
        volumeName,  
        MAX_PATH,  
        &serialNumber,  
        &maxComponentLength,  
        &fileSystemFlags,  
        fileSystemName,  
        MAX_PATH  
    );  
  
    if (isReady) {  
        ULARGE_INTEGER freeBytesAvailable, totalNumberOfBytes, totalNumberOfFreeBytes;  
        BOOL diskInfoSuccess = GetDiskFreeSpaceExA(  
            driveLetter.c_str(),  
            &freeBytesAvailable,  
            &totalNumberOfBytes,  
            &totalNumberOfFreeBytes  
        );  
  
        if (diskInfoSuccess) {  
            std::cout << "Drive: " << driveLetter << std::endl;  
            DI_driveLetter=driveLetter;
            std::cout << "Volume Name: " << volumeName << std::endl;  
            DI_volumeName=volumeName;
			std::cout << "File System: " << fileSystemName << std::endl;  
            DI_fileSystemName=fileSystemName;
			std::cout << "Total Space: " << totalNumberOfBytes.QuadPart / (1024.0 * 1024.0 * 1024.0) << " GB" << std::endl;  
            DI_totalSize_GB=double(totalNumberOfBytes.QuadPart / (1024.0 * 1024.0 * 1024.0));
			std::cout << "Free Space: " << freeBytesAvailable.QuadPart / (1024.0 * 1024.0 * 1024.0) << " GB" << std::endl; 
			DI_freeSize_GB=double(freeBytesAvailable.QuadPart / (1024.0 * 1024.0 * 1024.0));
        } else {  
            std::cout << "Failed to get disk information." << std::endl;  
        }  
    } else {  
        std::cout << "Failed to get volume information." << std::endl;  
    }  
}  
int main(){
	// 获取屏幕宽度和高度  
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);  
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);  
    
	initgraph(WINDOW_MAIN_SIZE_WIDTH,WINDOW_MAIN_SIZE_HEIGHT,0);//创建窗口  
	
	mainwindow.hwnd=getHWnd();//获取主窗口句柄 
	mainwindow.hinstance=getHInstance();//获取主进程实例句柄 
	mainwindow.hdc=getHDC();//获取图形接口设备上下文句柄 
	
	setcaption(APP_NAME_L);//设置窗口标题 
	movewindow(screenWidth-WINDOW_MAIN_SIZE_WIDTH+5,screenHeight-WINDOW_MAIN_SIZE_HEIGHT);//设置窗口显示在屏幕右下角 
    setrendermode(RENDER_MANUAL);//设置手动渲染模式，需要调用delay_fps()/delay_ms()等函数时才会更新窗口，可减少闪烁 
    ege_enable_aa(true);//开启窗口抗锯齿 
    
    setbkmode(TRANSPARENT);//设置文本输出带透明背景 
    setcolor(EGERGBA(255,255,255,100));//前景色
	
	std::string driveLetter = GetCurrentExecutableDriveLetter();  
    if (!driveLetter.empty()) {  //成功获取设备信息
        GetVolumeInfo(driveLetter);  
    }else{  //失败
    	setbkcolor_f(EGERGBA(0,0,0,100));
		cleardevice();
		PIMAGE IMG_WARNING=newimage();
		if(getimage(IMG_WARNING,"./resource/warning.png")!=grOk){
    		MessageBox(mainwindow.hwnd,"\"./resource/warning.png\" file not found.","Warning!",MB_OK+16); 
			exit(-1);
		}
		settextjustify(CENTER_TEXT,CENTER_TEXT);
		LOGFONTA f;
		getfont(&f);                          // 获取当前字体设置
		f.lfHeight = 48;                      // 设置字体高度为 48（包含行距）
		strcpy(f.lfFaceName, "黑体");         // 设置字体为“黑体”
		f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
		setfont(&f);                          // 设置字体样式
		outtextxy(10,(WINDOW_MAIN_SIZE_HEIGHT-200)/2+200+20,"检测当前设备信息失败");
		putimage((WINDOW_MAIN_SIZE_WIDTH-200)/2,(WINDOW_MAIN_SIZE_HEIGHT-200)/2,200,200,IMG_WARNING,0,0,800,800);
		std::cout << "Failed to determine the drive letter of the current executable." << std::endl; 
		getch();
		return 0; 
    } 
    
	PIMAGE FTSLOGO=newimage();
	if (getimage(FTSLOGO, "./resource/537logo.png")!= grOk) {
    	//读取图片文件失败
    	exit(-1);
	}
	putimage(5,5,100,100,FTSLOGO,0,0,743,743);
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
