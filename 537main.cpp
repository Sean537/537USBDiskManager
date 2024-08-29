/*
537 USB Disk Manager
Version 1.0 Beta

537main.cpp

Copyright(C)537 Studio.2024.All rights reserved.
*/

//EGE��API�ĵ���https://xege.org/manual/api/index.htm


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
	
	setcaption(APP_NAME_L);//���ô��ڱ���
	cout<<"Set window title: "<<APP_NAME_L<<"\n";
	movewindow(scr.width-WINDOW_MAIN_SIZE_WIDTH+5,scr.height-WINDOW_MAIN_SIZE_HEIGHT-30);//���ô�����ʾ����Ļ���½� 
    cout<<"Move window to: "<<scr.width-WINDOW_MAIN_SIZE_WIDTH+5<<", "<<scr.height-WINDOW_MAIN_SIZE_HEIGHT-30<<"\n";
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
    cout<<"Set color: "<<255<<", "<<255<<", "<<255<<", "<<100<<"\n\n";
    
	PIMAGE FTSLOGO=newimage();
	if(getimage(FTSLOGO,"./resource/537logo.png")!=grOk){
    	//��ȡͼƬ�ļ�ʧ��
    	cout<<"Load FTSLOGO failed.\n";
    	file_lost(INFO_IMAGE,"FTSLOGO");
	}else{
		cout<<"Load FTSLOGO successed.\n";
	}
	putimage(5,5,100,100,FTSLOGO,0,0,743,743);
	cout<<"Put FTSLOGO to: "<<"x="<<5<<" y="<<5<<" width="<<100<<" height="<<100<<"\n";
	outtextxy(110,15,DriveLetter);
	outtextxy(110,35,VolumeName);
	outtextxy(110,55,FileSystemName);
	char space[MAX_PATH]={};
	strcpy(space,FreeSpaceStr);
	strcat(space," / ");
	strcat(space,TotalSpaceStr);
	outtextxy(110,75,space);
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
