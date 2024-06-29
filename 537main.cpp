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

std::string DI_driveLetter="?";//��� 
std::string DI_volumeName="This Disk";//������
std::string DI_fileSystemName="None";//�ļ�ϵͳ����
double DI_totalSize_GB=0.0;//�ܿռ䣨GB��
double DI_freeSize_GB=0.0;//ʣ��ռ䣨GB��  

std::string GetCurrentExecutableDriveLetter();
void GetVolumeInfo(const std::string& driveLetter); 

int main(){
	// ��ȡ��Ļ��Ⱥ͸߶�  
    scr.width = GetSystemMetrics(SM_CXSCREEN);  
    scr.height = GetSystemMetrics(SM_CYSCREEN);  
    
	initgraph(WINDOW_MAIN_SIZE_WIDTH,WINDOW_MAIN_SIZE_HEIGHT,0);//��������  
	
	mainwindow.hwnd=getHWnd();//��ȡ�����ھ�� 
	mainwindow.hinstance=getHInstance();//��ȡ������ʵ����� 
	mainwindow.hdc=getHDC();//��ȡͼ�νӿ��豸�����ľ�� 
	
	setcaption(APP_NAME_L);//���ô��ڱ��� 
	movewindow(scr.width-WINDOW_MAIN_SIZE_WIDTH+5,scr.height-WINDOW_MAIN_SIZE_HEIGHT);//���ô�����ʾ����Ļ���½� 
    setrendermode(RENDER_MANUAL);//�����ֶ���Ⱦģʽ����Ҫ����delay_fps()/delay_ms()�Ⱥ���ʱ�Ż���´��ڣ��ɼ�����˸ 
    ege_enable_aa(true);//�������ڿ���� 
    
    settextjustify(CENTER_TEXT,CENTER_TEXT);//�����ı��������Ҿ��� 
    setbkmode(TRANSPARENT);//�����ı������͸������ 
    setcolor(EGERGBA(255,255,255,100));//ǰ��ɫ
	
	std::string driveLetter = GetCurrentExecutableDriveLetter();  
    if (!driveLetter.empty()) {  //�ɹ���ȡ�豸��Ϣ
        GetVolumeInfo(driveLetter);  
        std::ostringstream oss;  
    	oss << DI_totalSize_GB; // ��doubleת��Ϊstring  
    	std::string sDI_totalSize_GB = oss.str(); // ��ȡת�����string 
    	oss << DI_freeSize_GB;   
    	std::string sDI_freeSize_GB = oss.str(); 
        MessageBox(mainwindow.hwnd,DI_driveLetter.c_str(),"���",MB_OK+64);
        MessageBox(mainwindow.hwnd,DI_volumeName.c_str(),"������",MB_OK+64);
        MessageBox(mainwindow.hwnd,DI_fileSystemName.c_str(),"�ļ�ϵͳ����",MB_OK+64);
        MessageBox(mainwindow.hwnd,sDI_totalSize_GB.c_str(),"�ܿռ�",MB_OK+64);
        MessageBox(mainwindow.hwnd,sDI_freeSize_GB.c_str(),"ʣ��ռ�",MB_OK+64);
    }else{  //ʧ��
    	setbkcolor_f(EGERGBA(0,0,0,100));
		cleardevice();
		PIMAGE IMG_WARNING=newimage();
		if(getimage(IMG_WARNING,"./resource/warning.png")!=grOk){
    		MessageBox(mainwindow.hwnd,"\"./resource/warning.png\" file not found.","Warning!",MB_OK+16); 
			exit(-1);
		}
		LOGFONTA f;
		getfont(&f);                          // ��ȡ��ǰ��������
		f.lfHeight = 48;                      // ��������߶�Ϊ 48�������оࣩ
		strcpy(f.lfFaceName, "����");         // ��������Ϊ�����塱
		f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
		setfont(&f);                          // ����������ʽ
		outtextxy(10,(WINDOW_MAIN_SIZE_HEIGHT-200)/2+200+20,"��⵱ǰ�豸��Ϣʧ��");
		putimage((WINDOW_MAIN_SIZE_WIDTH-200)/2,(WINDOW_MAIN_SIZE_HEIGHT-200)/2,200,200,IMG_WARNING,0,0,800,800);
		std::cout << "Failed to determine the drive letter of the current executable." << std::endl; 
		getch();
		return 0; 
    } 
    
	PIMAGE FTSLOGO=newimage();
	if (getimage(FTSLOGO, "./resource/537logo.png")!= grOk) {
    	//��ȡͼƬ�ļ�ʧ��
    	exit(-1);
	}
	putimage(5,5,100,100,FTSLOGO,0,0,743,743);
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

std::string GetCurrentExecutableDriveLetter() {  
    char buffer[MAX_PATH];  
    GetModuleFileNameA(nullptr, buffer, MAX_PATH);  
    std::string path(buffer);  
    size_t pos = path.find_first_of(":");  
    if (pos != std::string::npos) {  
        return path.substr(0, pos + 1);  
    }  
    return ""; // û���ҵ���������  
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
