/*
537 USB Disk Manager
Version 1.0 Beta

537main.cpp

Copyright(C)537 Studio.2024.All rights reserved.
*/

//EGE库API文档：https://xege.org/manual/api/index.htm

#include "537UDM.h"
#include "include/main_window.h"

int main(){
	cmdwindow;
	
	// 获取屏幕宽度和高度  
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);  
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);  
    
	initgraph(WINDOW_MAIN_SIZE_WIDTH,WINDOW_MAIN_SIZE_HEIGHT,0);//创建窗口        1
	setcaption(APP_NAME_L);//设置窗口标题 
	movewindow(screenWidth-WINDOW_MAIN_SIZE_WIDTH,screenHeight-WINDOW_MAIN_SIZE_HEIGHT);
    setrendermode(RENDER_MANUAL);//设置手动渲染模式，需要调用delay_fps()/delay_ms()等函数时才会更新窗口，可减少闪烁 
    
	getch();//等待用户输入 

    closegraph();//关闭绘图窗口 
    return 0;
}
