/*
537 USB Disk Manager
Version 1.0 Beta

deviceinfo.cpp

Copyright (C) 537 Studio. 2024. All rights reserved.
*/
//#include "include/deviceinfo.h"
#include <iostream>
#include <windows.h>
char DriveLetter[3]={};
char VolumeName[MAX_PATH]={};  
char FileSystemName[MAX_PATH]={};  
char TotalSpaceStr[256]={};
char FreeSpaceStr[256]={}; 
// 辅助函数，用于将ULLONG转换为更易读的格式  
void ConvertSizeToString(ULONGLONG size,char* buffer,size_t bufferSize){  
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
  
int GetDeviceInfo(){  
    char modulePath[MAX_PATH]={0};  
    char driveRoot[3]={0};  
  
    // 获取当前可执行文件的完整路径  
    if(GetModuleFileNameA(NULL,modulePath,MAX_PATH)==0){ 
        std::cout<<"GetModuleFileNameA failed!"<<std::endl;  
        return 1;
    } 
  	
    // 从完整路径中提取盘符  
    driveRoot[0]=toupper(modulePath[0]);  
    driveRoot[1]=':';
    driveRoot[2]='/';
    driveRoot[3]='\0';  
  
    // 将盘符复制到全局变量中  
    strcpy(DriveLetter, driveRoot);  
    DriveLetter[2] = '\0'; // 确保DriveLetter以null结尾  
  
    // 获取卷信息  
    if (!GetVolumeInformationA(driveRoot,VolumeName,MAX_PATH,NULL,NULL,NULL,FileSystemName,MAX_PATH)) {  
        std::cout<<"GetVolumeInformationA failed!"<<std::endl;  
        return 2;  
    }  
  
    // 获取磁盘空间信息  
    ULARGE_INTEGER totalSpace, freeSpace, totalFreeSpace;  
    if (!GetDiskFreeSpaceExA(driveRoot, &freeSpace, &totalSpace, &totalFreeSpace)) {  
        std::cout<<"GetDiskFreeSpaceExA failed!"<<std::endl;  
        return 3;  
    }  
  
    // 转换空间大小为更易读的格式  
    ConvertSizeToString(totalSpace.QuadPart, TotalSpaceStr, sizeof(TotalSpaceStr));  
    ConvertSizeToString(freeSpace.QuadPart, FreeSpaceStr, sizeof(FreeSpaceStr));  
  
    // 输出结果  
    std::cout<<"DriveLetter: "<<DriveLetter<<std::endl;  
    std::cout<<"VolumeName: "<<VolumeName<<std::endl;  
    std::cout<<"FileSystemName: "<<FileSystemName<<std::endl;  
    std::cout<<"TotalSpace: "<<TotalSpaceStr<<std::endl;  
    std::cout<<"FreeSpace: "<<FreeSpaceStr<<std::endl<<std::endl;  
    
	return 0;
}
