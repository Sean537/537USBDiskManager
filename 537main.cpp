/*
537 USB Disk Manager
Version 1.0 Beta

537main.cpp

Copyright(C)537 Studio.2024.All rights reserved.
*/

//EGE��API�ĵ���https://xege.org/manual/api/index.htm

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
	// ��ȡ��Ļ��Ⱥ͸߶�  
    scr.width = GetSystemMetrics(SM_CXSCREEN);  
    scr.height = GetSystemMetrics(SM_CYSCREEN);  
    
	initgraph(WINDOW_MAIN_SIZE_WIDTH,WINDOW_MAIN_SIZE_HEIGHT,0);//��������  
	movewindow(scr.width-WINDOW_MAIN_SIZE_WIDTH,scr.height-WINDOW_MAIN_SIZE_HEIGHT);//���ô�����ʾ����Ļ���½� 
    setrendermode(RENDER_MANUAL);//�����ֶ���Ⱦģʽ����Ҫ����delay_fps()/delay_ms()�Ⱥ���ʱ�Ż���´��ڣ��ɼ�����˸ 
	ege_enable_aa(true);//�������ڿ���� 
	
	setcaption(APP_NAME_L);//���ô��ڱ���
	
	mainwindow.hwnd=getHWnd();//��ȡ�����ھ�� 
	mainwindow.hinstance=getHInstance();//��ȡ������ʵ����� 
	mainwindow.hdc=getHDC();//��ȡͼ�νӿ��豸�����ľ��  
    
    settextjustify(LEFT_TEXT,CENTER_TEXT);//�����ı��������Ҿ��� 
    setbkmode(TRANSPARENT);//�����ı������͸������ 
    setcolor(EGERGBA(255,255,255,100));//ǰ��ɫ
    
	PIMAGE FTSLOGO=newimage();
	if (getimage(FTSLOGO,"./resource/537logo.png")!=grOk) {
    	//��ȡͼƬ�ļ�ʧ��
    	file_lost(INFO_IMAGE,"FTSLOGO","resource/537logo.png");
	}
	putimage(5,5,100,100,FTSLOGO,0,0,743,743);
	
	outtextxy(110,5,DriveLetter);
	outtextxy(110,25,VolumeName);
	outtextxy(110,45,FileSystemName);
	//outtextrect(110,50,200,30,"This is a test. Just show the ege text out.");
	
	delimage(FTSLOGO); 
	
    /*
	setbkcolor();//����ɫ 
    setbkcolor_f();//��������ɫ
	setfillcolor();//���ɫ
	setfontbkcolor();//�ı�����ɫ
	
	ege_setalpha();//����ͳһ͸���� 
    */
	getch();//�ȴ��û����� 

    closegraph();//�رջ�ͼ���� 
    return 0;
}

// �������������ڽ�ULLONGת��Ϊ���׶��ĸ�ʽ  
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
    buffer[bufferSize - 1] = '\0'; // ȷ���ַ�����null��β  
}  
  
int GetDeviceInfo() {  
    char modulePath[MAX_PATH] = {0};  
    char driveRoot[3] = {0};  
  
    // ��ȡ��ǰģ�飨��ִ���ļ���������·��  
    if (GetModuleFileNameA(NULL, modulePath, MAX_PATH) == 0) {  
        std::cerr << "GetModuleFileNameA failed!" << std::endl;  
        return 2;  
    }  
  
    // ������·������ȡ�̷�  
    driveRoot[0] = toupper(modulePath[0]);  
    driveRoot[1] = ':';  
    driveRoot[2] = '\0';  
  
    // ���̷����Ƶ�ȫ�ֱ�����  
    strncpy(DriveLetter, driveRoot, 3);  
    DriveLetter[3] = '\0'; // ȷ��DriveLetter��null��β  
  
    // ��ȡ����Ϣ  
    if (!GetVolumeInformationA(driveRoot, VolumeName, MAX_PATH, NULL, NULL, NULL, FileSystemName, MAX_PATH)) {  
        std::cerr << "GetVolumeInformationA failed!" << std::endl;  
        return 3;  
    }  
  
    // ��ȡ���̿ռ���Ϣ  
    ULARGE_INTEGER totalSpace, freeSpace, totalFreeSpace;  
    if (!GetDiskFreeSpaceExA(driveRoot, &freeSpace, &totalSpace, &totalFreeSpace)) {  
        std::cerr << "GetDiskFreeSpaceExA failed!" << std::endl;  
        return 4;  
    }  
  
    // ת���ռ��СΪ���׶��ĸ�ʽ  
    ConvertSizeToString(totalSpace.QuadPart, TotalSpaceStr, sizeof(TotalSpaceStr));  
    ConvertSizeToString(freeSpace.QuadPart, FreeSpaceStr, sizeof(FreeSpaceStr));  
  
    // ������  
    std::cout << "DriveLetter: " << DriveLetter << std::endl;  
    std::cout << "VolumeName: " << VolumeName << std::endl;  
    std::cout << "FileSystemName: " << FileSystemName << std::endl;  
    std::cout << "TotalSpace: " << TotalSpaceStr << std::endl;  
    std::cout << "FreeSpace: " << FreeSpaceStr << std::endl;  
    
	return 1;
}
