# 537U盘管理器

## 简介

这是一个方便的U盘文件管理器，可以被安装在U盘等移动介质上。尚在开发中。

您可以自如访问这张磁盘上存储的程序、文档、图片、音乐、视频，添加便携式应用，分类排版都是程序自动控制的而无需人工操作，各种文件的访问也比资源管理器简单。

它使您的U盘文件井然有序，同时优雅简洁的交互也提高了使用体验，是您的U盘必备应用。

## 开发

需要在 Windows 操作系统环境里，使用 C++11 或更高语言版本编译。

#### Release

```G++
mingw32-make all
```

#### Debug

```G++
#生成OBJ文件
g++ -DDEBUG -c 537main.cpp -o 537main.o -std=c++11 -g3 -DDEBUG
g++ -DDEBUG -c gif.cpp -o gif.o -std=c++11 -g3 -DDEBUG
g++ -DDEBUG -c wronginfo.cpp -o wronginfo.o -std=c++11 -g3 -DDEBUG
g++ -DDEBUG -c deviceinfo.cpp -o deviceinfo.o -std=c++11 -g3 -DDEBUG
g++ -DDEBUG -c dpi.cpp -o dpi.o -std=c++11 -g3 -DDEBUG
g++ -DDEBUG -c file.cpp -o file.o -std=c++11 -g3 -DDEBUG

#生成资源文件
windres -i 537_USB_Disk_Manager_private.rc --input-format=rc -o 537_USB_Disk_Manager_private.res -O coff  --include-dir ./resource

#整合成可执行文件
g++ -DDEBUG 537main.o gif.o wronginfo.o deviceinfo.o dpi.o file.o 537_USB_Disk_Manager_private.res -o "537 USB Disk Manager.exe" -static-libgcc -L"./lib" -mwindows -lgraphics -lgdiplus -luuid -lmsimg32 -lgdi32 -limm32 -lole32 -loleaut32 -lwinmm -g3
```