/*
537 USB Disk Manager
Version 1.0 Beta

537main.cpp

Copyright(C)537 Studio.2024.All rights reserved.
*/

//EGE��API�ĵ���https://xege.org/manual/api/index.htm

#include "graphics.h" 
#include "537UDM.h"
#include "include/main_window.h"

int main(){
	cmdwindow;
	
	// ��ȡ��Ļ��Ⱥ͸߶�  
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);  
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);  
    
	initgraph(WINDOW_MAIN_SIZE_WIDTH,WINDOW_MAIN_SIZE_HEIGHT,0);//��������        1
	setcaption(APP_NAME_L);//���ô��ڱ��� 
	movewindow(screenWidth-WINDOW_MAIN_SIZE_WIDTH+5,screenHeight-WINDOW_MAIN_SIZE_HEIGHT);//���ô�����ʾ����Ļ���½� 
    setrendermode(RENDER_MANUAL);//�����ֶ���Ⱦģʽ����Ҫ����delay_fps()/delay_ms()�Ⱥ���ʱ�Ż���´��ڣ��ɼ�����˸ 
    ege_enable_aa(true);//�������ڿ���� 
    
    setbkmode(TRANSPARENT);//�����ı������͸������ 
    setcolor(EGERGBA(255,255,255,100));//ǰ��ɫ
	
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
