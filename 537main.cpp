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

std::string DI_driveLetter="?";//��� 
std::string DI_volumeName="This Disk";//������
std::string DI_fileSystemName="None";//�ļ�ϵͳ����
double DI_totalSize_GB=0.0;//�ܿռ䣨GB��
double DI_freeSize_GB=0.0;//ʣ��ռ䣨GB��  

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
    
    settextjustify(LEFT_TEXT,CENTER_TEXT);//�����ı��������Ҿ��� 
    setbkmode(TRANSPARENT);//�����ı������͸������ 
    setcolor(EGERGBA(255,255,255,100));//ǰ��ɫ
    
	PIMAGE FTSLOGO=newimage();
	if (getimage(FTSLOGO,"./resource/537logo.png")!=grOk) {
    	//��ȡͼƬ�ļ�ʧ��
    	file_lost(INFO_IMAGE,"FTSLOGO","./resource/537logo.png");
	}
	putimage(5,5,100,100,FTSLOGO,0,0,743,743);
	
	outtextxy(110,5,"Device name");
	outtextrect(110,50,200,30,"This is a test. Just show the ege text out.");
	
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
