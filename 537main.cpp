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
using namespace std;

double dpi=1.0;
void GetDPI()
{
    HWND hd=GetDesktopWindow();
    HDC hdc=GetDC(NULL);
	RECT rect;
	GetClientRect(hd,&rect);
	int cw1=(rect.right-rect.left),cw2=GetDeviceCaps(hdc,DESKTOPHORZRES);
	//cw2��ȡ��ʾ��ʵ�ʷֱ��ʣ�cw1��ȡ���ź�ķֱ���
	//��4K 150%�����£�ʵ�ʷֱ���Ϊ3840x2160�����ź�ķֱ���Ϊ2560x1440
    dpi=1.0*cw2/cw1;
	//��ʱ��ȡ��dpiֵΪ1.5
}
void EnableHighDPI()
{
    HWND hd=GetDesktopWindow();
    HDC hdc=GetDC(NULL);
	RECT rect;
	GetClientRect(hd,&rect);
	int cw1=(rect.right-rect.left),cw2=GetDeviceCaps(hdc,DESKTOPHORZRES);
    dpi=1.0*cw2/cw1;
    HINSTANCE hUser32=LoadLibrary("User32.dll");
    if(hUser32){
        typedef BOOL (WINAPI* LPSetProcessDPIAware)(void);
        LPSetProcessDPIAware pSetProcessDPIAware=(LPSetProcessDPIAware)GetProcAddress(hUser32,"SetProcessDPIAware");
        if(pSetProcessDPIAware)pSetProcessDPIAware();
        FreeLibrary(hUser32);
    }
}

int main(){
	GetDPI();
	EnableHighDPI();
	fShowConsoleWindow;
	if(GetDeviceInfo()!=0){
		get_system_info_failed();
	}
	
	// ��ȡ��Ļ��Ⱥ͸߶�  
    scr.width = GetSystemMetrics(SM_CXSCREEN);  
    scr.height = GetSystemMetrics(SM_CYSCREEN);  
    cout<<"Get screen width: "<<scr.width<<"px\n";
    cout<<"Get screen height: "<<scr.height<<"px\n\n";
    
	initgraph(WINDOW_MAIN_SIZE_WIDTH*dpi,WINDOW_MAIN_SIZE_HEIGHT*dpi,0);//��������  
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
	outtextxy(110*dpi,15*dpi,DriveLetter);
	outtextxy(110*dpi,35*dpi,VolumeName);
	outtextxy(110*dpi,55*dpi,FileSystemName);
	char space[MAX_PATH]={};
	strcpy(space,FreeSpaceStr);
	strcat(space," / ");
	strcat(space,TotalSpaceStr);
	outtextxy(110,75,space);
	
	ege_fillrect(0*dpi,200*dpi,400*dpi,200*dpi); 
	putimage_withalpha(NULL,FTSLOGO,75,250,100,100,0,0,743,743);
	Sleep(1000);
	for(int i=0;i<=100;i++){
		setfillcolor(EGERGBA(0,122,255,i));
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
	
	//outtextrect(110,50,200,30,"This is a test. Just show the ege text out.");
	
	delimage(FTSLOGO); 
	
	
	Gif gif(L"resource/loader1.gif");
	gif.setPos(30,150);
	gif.setSize(48,48);
	gif.info();//����̨���Gifͼ����Ϣ
	gif.play();

	for (; is_run(); delay_fps(60)) {
		gif.draw();
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
