/*
537 USB Disk Manager
Version 1.0 Beta

537main.cpp

Copyright(C)537 Studio.2024.All rights reserved.
*/

//EGE库API文档：https://xege.org/manual/api/index.htm

#include "graphics.h" 
#include "537UDM.h"
#include "include/main_window.h"

int main(){
	cmdwindow;
	
	// 获取屏幕宽度和高度  
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);  
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);  
    
	initgraph(WINDOW_MAIN_SIZE_WIDTH,WINDOW_MAIN_SIZE_HEIGHT,0);//创建窗口        1
	setcaption(APP_NAME_L);//设置窗口标题 
	movewindow(screenWidth-WINDOW_MAIN_SIZE_WIDTH+5,screenHeight-WINDOW_MAIN_SIZE_HEIGHT);//设置窗口显示在屏幕右下角 
    setrendermode(RENDER_MANUAL);//设置手动渲染模式，需要调用delay_fps()/delay_ms()等函数时才会更新窗口，可减少闪烁 
    ege_enable_aa(true);//开启窗口抗锯齿 
    
    setbkmode(TRANSPARENT);//设置文本输出带透明背景 
    setcolor(EGERGBA(255,255,255,100));//前景色
	
	PIMAGE FTSLOGO=newimage();
	if (getimage(FTSLOGO, "./resource/537logo.png")!= grOk) {
    	//读取图片文件失败
    	exit(-1);
	}
	putimage(5,5,100,100,FTSLOGO,0,0,743,743);
	delimage(FTSLOGO); 
    /*
	setbkcolor();//背景色 
    setbkcolor_f();//清屏背景色
	setfillcolor();//填充色
	setfontbkcolor();//文本背景色
	
	ege_setalpha();//设置统一透明度 
    */
	getch();//等待用户输入 

    closegraph();//关闭绘图窗口 
    return 0;
}
