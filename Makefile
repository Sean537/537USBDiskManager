# Project: 537 USB Disk Manager
# Makefile created by Dev-C++ 5.11, edited by Sean537 in 537 Studio

CPP      = g++.exe -D__DEBUG__
CC       = gcc.exe -D__DEBUG__
WINDRES  = windres.exe
RES      = 537UDM_AppInfo.res
OBJ      = 537main.o gif.o wronginfo.o deviceinfo.o dpi.o file.o $(RES)
LINKOBJ  = 537main.o gif.o wronginfo.o deviceinfo.o dpi.o file.o $(RES)
LIBS     = -L"C:/Program Files (x86)/Dev-Cpp/MinGW64/lib" -L"C:/Program Files (x86)/Dev-Cpp/MinGW64/x86_64-w64-mingw32/lib" -static-libgcc -L"./lib" -mwindows -lgraphics -lgdiplus -luuid -lmsimg32 -lgdi32 -limm32 -lole32 -loleaut32 -lwinmm -lnetpp -g3
INCS     = -I"C:/Program Files (x86)/Dev-Cpp/MinGW64/include" -I"C:/Program Files (x86)/Dev-Cpp/MinGW64/x86_64-w64-mingw32/include" -I"C:/Program Files (x86)/Dev-Cpp/MinGW64/lib/gcc/x86_64-w64-mingw32/4.9.2/include"
CXXINCS  = -I"C:/Program Files (x86)/Dev-Cpp/MinGW64/include" -I"C:/Program Files (x86)/Dev-Cpp/MinGW64/x86_64-w64-mingw32/include" -I"C:/Program Files (x86)/Dev-Cpp/MinGW64/lib/gcc/x86_64-w64-mingw32/4.9.2/include" -I"C:/Program Files (x86)/Dev-Cpp/MinGW64/lib/gcc/x86_64-w64-mingw32/4.9.2/include/c++"
BIN      = "537 USB Disk Manager.exe"
CXXFLAGS = $(CXXINCS) -std=c++11 -g3 -DDEBUG
CFLAGS   = $(INCS) -std=c++11 -g3
RM       = rm.exe -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o $(BIN) $(LIBS)

537main.o: 537main.cpp
	$(CPP) -c 537main.cpp -o 537main.o $(CXXFLAGS)

gif.o: gif.cpp
	$(CPP) -c gif.cpp -o gif.o $(CXXFLAGS)

wronginfo.o: wronginfo.cpp
	$(CPP) -c wronginfo.cpp -o wronginfo.o $(CXXFLAGS)

deviceinfo.o: deviceinfo.cpp
	$(CPP) -c deviceinfo.cpp -o deviceinfo.o $(CXXFLAGS)

dpi.o: dpi.cpp
	$(CPP) -c dpi.cpp -o dpi.o $(CXXFLAGS)

file.o: file.cpp
	$(CPP) -c file.cpp -o file.o $(CXXFLAGS)

537UDM_AppInfo.res: 537UDM_AppInfo.rc resource.rc
	$(WINDRES) -i 537UDM_AppInfo.rc --input-format=rc -o 537UDM_AppInfo.res -O coff  --include-dir ./resource

