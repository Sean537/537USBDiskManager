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

// �������������ڽ�ULLONGת��Ϊ���׶��ĸ�ʽ  
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
    buffer[bufferSize-1]='\0'; // ȷ���ַ�����null��β  
}  
  
int GetDeviceInfo() {  
    char modulePath[MAX_PATH]={0};  
    char driveRoot[3]={0};  
  
    // ��ȡ��ǰ��ִ���ļ�������·��  
    if(GetModuleFileNameA(NULL,modulePath,MAX_PATH)==0){ 
        cout<<"GetModuleFileNameA failed!"<<endl;  
        return 1;
    } 
  	
    // ������·������ȡ�̷�  
    driveRoot[0]=toupper(modulePath[0]);  
    driveRoot[1]=':';
    driveRoot[2]='/';
    driveRoot[3]='\0';  
  
    // ���̷����Ƶ�ȫ�ֱ�����  
    strncpy(DriveLetter, driveRoot, 4);  
    DriveLetter[2] = '\0'; // ȷ��DriveLetter��null��β  
  
    // ��ȡ����Ϣ  
    if (!GetVolumeInformationA(driveRoot,VolumeName,MAX_PATH,NULL,NULL,NULL,FileSystemName,MAX_PATH)) {  
        cout<<"GetVolumeInformationA failed!"<<endl;  
        return 2;  
    }  
  
    // ��ȡ���̿ռ���Ϣ  
    ULARGE_INTEGER totalSpace, freeSpace, totalFreeSpace;  
    if (!GetDiskFreeSpaceExA(driveRoot, &freeSpace, &totalSpace, &totalFreeSpace)) {  
        cout<<"GetDiskFreeSpaceExA failed!"<<endl;  
        return 3;  
    }  
  
    // ת���ռ��СΪ���׶��ĸ�ʽ  
    ConvertSizeToString(totalSpace.QuadPart, TotalSpaceStr, sizeof(TotalSpaceStr));  
    ConvertSizeToString(freeSpace.QuadPart, FreeSpaceStr, sizeof(FreeSpaceStr));  
  
    // ������  
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
	
	// ��ȡ��Ļ��Ⱥ͸߶�  
    scr.width = GetSystemMetrics(SM_CXSCREEN);  
    scr.height = GetSystemMetrics(SM_CYSCREEN);  
    cout<<"Get screen width: "<<scr.width<<"px\n";
    cout<<"Get screen height: "<<scr.height<<"px\n\n";
    
	initgraph(WINDOW_MAIN_SIZE_WIDTH,WINDOW_MAIN_SIZE_HEIGHT,0);//��������  
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
	
	setcaption(APP_NAME_L);//���ô��ڱ���
	cout<<"Set window title: "<<APP_NAME_L<<"\n";
	movewindow(mainwindow.x,mainwindow.y);//���ô�����ʾ����Ļ���½� 
    cout<<"Move window to: "<<mainwindow.x<<", "<<mainwindow.y<<"\n";
	setrendermode(RENDER_MANUAL);//�����ֶ���Ⱦģʽ����Ҫ����delay_fps()/delay_ms()�Ⱥ���ʱ�Ż���´��ڣ��ɼ�����˸ 
	cout<<"Set render mode\n";
    ege_enable_aa(true);//�������ڿ���� 
    cout<<"Enable aa\n\n";
	
	mainwindow.hwnd=getHWnd();//��ȡ�����ھ�� 
	cout<<"Get HWnd: "<<mainwindow.hwnd<<"\n";
	mainwindow.hinstance=getHInstance();//��ȡ������ʵ�����
	cout<<"Get HInstance: "<<mainwindow.hinstance<<"\n";
	mainwindow.hdc=getHDC();//��ȡͼ�νӿ��豸�����ľ�� 
	cout<<"Get HDC: "<<mainwindow.hdc<<"\n\n";
    
    settextjustify(LEFT_TEXT,CENTER_TEXT);//�����ı��������Ҿ��� 
    cout<<"Set text location mode: "<<LEFT_TEXT<<", "<<CENTER_TEXT<<"\n";
    setbkmode(TRANSPARENT);//�����ı������͸������ 
    cout<<"Set background mode: "<<TRANSPARENT<<"\n";
    setcolor(EGERGBA(255,255,255,100));//ǰ��ɫ
    setfillcolor(EGERGB(1,182,19));
    cout<<"Set color: "<<255<<", "<<255<<", "<<255<<", "<<100<<"\n\n";
    
	PIMAGE FTSLOGO=newimage();
	if(getimage(FTSLOGO,"./resource/537logo.png")!=grOk){
    	//��ȡͼƬ�ļ�ʧ��
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
	setbkcolor();//����ɫ 
    setbkcolor_f();//��������ɫ
	setfillcolor();//���ɫ
	setfontbkcolor();//�ı�����ɫ
	
	ege_setalpha();//����ͳһ͸���� 
    */
	getch;//�ȴ��û����� 
    closegraph();//�رջ�ͼ���� 
    return 0;
}
