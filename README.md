# 537U盘管理器

## 简介

这是一个方便的U盘文件管理器，可以被安装在U盘等移动介质上。尚在开发中。

您可以自如访问这张磁盘上存储的程序、文档、图片、音乐、视频，添加便携式应用，分类排版都是程序自动控制的而无需人工操作，各种文件的访问也比资源管理器简单。

它使您的U盘文件井然有序，同时优雅简洁的交互也提高了使用体验，是您的U盘必备应用。

## 开发

需要在 Windows 操作系统环境里，使用 C++11 或更高语言版本编译。

推荐使用 MinGW 4.9.2 （该编译器也被内置在 Dev-C++ 5.11 里）。

#### Release

```MinGW
mingw32-make
```

或

```MinGW
mingw32-make MODE=RELEASE
```

#### Debug

```MinGW
mingw32-make MODE=DEBUG
```

#### Clean

```MinGW
mingw32-make MODE=DEBUG
```