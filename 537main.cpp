/*
537 USB Disk Manager
Version 1.0 Beta

537main.cpp

Copyright(C)537 Studio.2024.All rights reserved.
*/

//EGE¿âAPIÎÄµµ£ºhttps://xege.org/manual/api/index.htm

#include "537DM.h"
#include "include/main_window.h"
int main(){
	initgraph(WINDOW_MAIN_SIZE_WIDTH,WINDOW_MAIN_SIZE_HEIGHT,0);
	
    setcaption(APP_NAME_L);
    setrendermode(RENDER_MANUAL);
	getch();

    closegraph();
    return 0;
}
