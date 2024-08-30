/*
537 USB Disk Manager
Version 1.0 Beta

537main.cpp

Copyright (C) 537 Studio. 2024. All rights reserved.
*/

//EGE��API�ĵ���https://xege.org/manual/api/index.htm

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
#include "resource.h"

using namespace std;


int main(){
	fShowConsoleWindow;//��ʾ�����д��� 
	
	if(GetDeviceInfo()!=0){//��ȡ�豸��Ϣʧ�� 
		get_system_info_failed();
	}
	
	// ��ȡ��Ļ��Ⱥ͸߶�  
    scr.width = GetSystemMetrics(SM_CXSCREEN);  
    cout<<"Get screen width: "<<scr.width<<"px\n";
	scr.height = GetSystemMetrics(SM_CYSCREEN);  
    cout<<"Get screen height: "<<scr.height<<"px\n\n";
    
	
	
	taskbar.hwnd=::FindWindow("Shell_TrayWnd","");//��ȡ������hwnd��Ϣ 
	cout<<"Get taskbar hwnd: "<<taskbar.hwnd<<"\n";
	::GetWindowRect(taskbar.hwnd,&taskbar.rect);//��ȡ����������rect��Ϣ 
	cout<<"Get taskbar rect\n";
	taskbar.x=taskbar.rect.left;//��������������x���� 
	cout<<"Taskbar's x: "<<taskbar.x<<"\n";
	taskbar.y=taskbar.rect.top;//��������������y���� 
	cout<<"Taskbar's y: "<<taskbar.y<<"\n";
	taskbar.width=taskbar.rect.right-taskbar.rect.left;//�������������ڿ�� 
	cout<<"Taskbar's width: "<<taskbar.width<<"\n";
	taskbar.height=taskbar.rect.bottom-taskbar.rect.top;//�������������ڸ߶� 
	cout<<"Taskbar's height: "<<taskbar.height<<"\n\n";
	
	mainwindow.width=WINDOW_MAIN_SIZE_WIDTH;//�����ڿ�� 
	cout<<"Main window's width: "<<mainwindow.width<<"\n";
	mainwindow.height=WINDOW_MAIN_SIZE_HEIGHT;//�����ڸ߶� 
	cout<<"Main window's height: "<<mainwindow.height<<"\n";
	mainwindow.x=scr.width-mainwindow.width;//������x���� 
	cout<<"Main window's x: "<<mainwindow.x<<"\n";
	mainwindow.y=scr.height-mainwindow.height-taskbar.height;//������y���� 
	cout<<"Main window's y: "<<mainwindow.y<<"\n\n";
	
	setcaption(APP_NAME_L);//���ô��ڱ���
	cout<<"Set window title: "<<APP_NAME_L<<"\n";
	setinitmode(0,mainwindow.x,mainwindow.y);//���ó�ʼ������λ������Ļ���½� 
	cout<<"Set window location: "<<mainwindow.x<<", "<<mainwindow.y<<"\n";
	initgraph(WINDOW_MAIN_SIZE_WIDTH*dpi,WINDOW_MAIN_SIZE_HEIGHT*dpi,0);//��������  
	cout<<"Create window\n";
	setrendermode(RENDER_MANUAL);//�����ֶ���Ⱦģʽ����Ҫ����delay_fps()/delay_ms()�Ⱥ���ʱ�Ż���´��ڣ��ɼ�����˸ 
	cout<<"Set render mode\n";
    ege_enable_aa(true);//�������ڿ���� 
    cout<<"Enable aa\n\n";
	
	GetDPI();//��ȡϵͳDPI 
	EnableHighDPI();//�������ø���DPI 
	
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
    cout<<"Set color: "<<255<<", "<<255<<", "<<255<<", "<<100<<"\n";
    setfillcolor(EGERGB(1,182,19));
    cout<<"Set fill color: "<<1<<", "<<182<<", "<<19<<"\n\n";
    
	PIMAGE FTSLOGO=newimage();
	if(getimage(FTSLOGO,"./resource/537logo.png")!=grOk){
    	//��ȡͼƬ�ļ�ʧ��
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
	editBox.create(1);						//������false��ʾ���У�true��ʾ����
	editBox.setreadonly(false);		//�����������������
	editBox.move(100, 100);						//����λ��
	editBox.size(200,100);	//���óߴ�
	editBox.setmaxlen(20);						//��������������ַ���
	editBox.setfont(20*dpi,8*dpi,"΢���ź�");
	editBox.visible(true);						//���ÿɼ���
	editBox.settext("");
	editBox.setfocus();							//���û�ȡ����
	cout<<"\nCreate editbox\n\n";
	//outtextrect(110,50,200,30,"This is a test. Just show the ege text out.");
	
	delimage(FTSLOGO); 
	
	
	Gif gif(L"resource/loader1.gif");
	cout<<"Load GIF\n";
	gif.setPos(30,150);
	cout<<"Set GIF pos: 30,150\n";
	gif.setSize(48,48);
	cout<<"Set GIF size: 48,48\n";
	gif.info();//����̨���Gifͼ����Ϣ
	gif.play();
	cout<<"Draw GIF...\n\n";
	for(int i=0;i<=100;i++,delay_fps(60)) {
		gif.draw();
		
	}
	
	string directoryPath="."; // ��ʾ��ǰĿ¼
    vector<string> exeFiles;
    // ɨ�赱ǰĿ¼����������Ŀ¼
    cout<<"Scanning EXE files...\n";
	ScanDirectoryForExe(directoryPath, exeFiles);
    // ��ӡ�����ҵ���.exe�ļ�·��
    for(const auto& file:exeFiles){
        std::cout << file << std::endl;
    }
    /*
	setbkcolor();//����ɫ 
    setbkcolor_f();//��������ɫ
	setfillcolor();//���ɫ
	setfontbkcolor();//�ı�����ɫ
	
	ege_setalpha();//����ͳһ͸���� 
    */
    while(true){
    	
	}
	fgetch;//�ȴ��û����� 
    closegraph();//�رջ�ͼ���� 
    return 0;
}
