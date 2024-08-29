/*
537 USB Disk Manager
Version 1.0 Beta

537UDM.h

Copyright(C)537 Studio.2024.All rights reserved.
*/

#define APP_NAME_L "537 USB Disk Manager"
#define APP_NAME_S "537UDM"
#define APP_NAME_CN "537U盘管理器"

#define APP_VERSION "1.0 Beta" 
#define APP_BUILDVERSION "2024.8.12.0"

#define APP_DEVELOPER "537 Studio"
#define APP_DEVELOPER_CN "537工作室"

#define WINDOW_MAIN_SIZE_WIDTH 400
#define WINDOW_MAIN_SIZE_HEIGHT 600

#include <iostream>
#include <string> 
#include <sstream>  
#include <windows.h>  
using namespace std;

char DriveLetter[3]={0};  
char VolumeName[MAX_PATH]={0};  
char FileSystemName[MAX_PATH]={0};  
char TotalSpaceStr[256]={0};  
char FreeSpaceStr[256]={0}; 

struct screenSize{
	int width;
	int height;
}scr;

struct WindowInfo{
	HWND hwnd;//窗口句柄 
	HINSTANCE hinstance;//主进程实例句柄
	HDC hdc;//图形设备上下文句柄
}mainwindow;

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
