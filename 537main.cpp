/*
537 USB Disk Manager
Version 1.0 Beta

537main.cpp

Copyright(C)537 Studio.2024.All rights reserved.
*/

//EGE��API�ĵ���https://xege.org/manual/api/index.htm

#include "537UDM.h"
#include "include/main_window.h"

int main(){
	cmdwindow;
	
	// ��ȡ��Ļ��Ⱥ͸߶�  
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);  
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);  
    
	initgraph(WINDOW_MAIN_SIZE_WIDTH,WINDOW_MAIN_SIZE_HEIGHT,0);//��������        1
	setcaption(APP_NAME_L);//���ô��ڱ��� 
	movewindow(screenWidth-WINDOW_MAIN_SIZE_WIDTH,screenHeight-WINDOW_MAIN_SIZE_HEIGHT);
    setrendermode(RENDER_MANUAL);//�����ֶ���Ⱦģʽ����Ҫ����delay_fps()/delay_ms()�Ⱥ���ʱ�Ż���´��ڣ��ɼ�����˸ 
    
	getch();//�ȴ��û����� 

    closegraph();//�رջ�ͼ���� 
    return 0;
}
