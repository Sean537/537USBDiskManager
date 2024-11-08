# Project: 537 USB Disk Manager
# Makefile created by Dev-C++ 5.11, edited by Sean537 in 537 Studio

MODE=RELEASE


ifeq ($(MODE), DEBUG)
CPP      = g++.exe -DDEBUG
CC       = gcc.exe -DDEBUG
LIBS     = -static-libgcc -L"./lib" -mwindows -lgraphics_4.9.2 -lgdiplus -luuid -lmsimg32 -lgdi32 -limm32 -lole32 -loleaut32 -lwinmm -lnetpp -g3
CXXFLAGS = $(CXXINCS) -std=c++11 -g3 -DDEBUG
CFLAGS   = $(INCS) -std=c++11 -g3
else
CPP      = g++.exe
CC       = gcc.exe
LIBS     = -static-libgcc -L"./lib" -mwindows -lgraphics_4.9.2 -lgdiplus -luuid -lmsimg32 -lgdi32 -limm32 -lole32 -loleaut32 -lwinmm -lnetpp
CXXFLAGS = $(CXXINCS) -std=c++11
CFLAGS   = $(INCS) -std=c++11
endif

WINDRES  = windres.exe
RES      = 537UDM_AppInfo.res
OBJ      = 537main.o gif.o wronginfo.o deviceinfo.o dpi.o file.o $(RES)
LINKOBJ  = 537main.o gif.o wronginfo.o deviceinfo.o dpi.o file.o $(RES)
BIN      = 537UDM.exe
RM       = rm.exe -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after
	@echo Starting 537UDM...
	@${BIN}

clean: clean-custom
	${RM} $(OBJ) $(BIN)
	@echo Clean successful.

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o $(BIN) $(LIBS)
	@echo Link object to exe.

537main.o: 537main.cpp
	$(CPP) -c 537main.cpp -o 537main.o $(CXXFLAGS)
	@echo Build 537main.

gif.o: gif.cpp
	$(CPP) -c gif.cpp -o gif.o $(CXXFLAGS)
	@echo Build gif.

wronginfo.o: wronginfo.cpp
	$(CPP) -c wronginfo.cpp -o wronginfo.o $(CXXFLAGS)
	@echo Build wronginfo.

deviceinfo.o: deviceinfo.cpp
	$(CPP) -c deviceinfo.cpp -o deviceinfo.o $(CXXFLAGS)
	@echo Build deviceinfo.

dpi.o: dpi.cpp
	$(CPP) -c dpi.cpp -o dpi.o $(CXXFLAGS)
	@echo Build dpi.

file.o: file.cpp
	$(CPP) -c file.cpp -o file.o $(CXXFLAGS)
	@echo Build file.

537UDM_AppInfo.res: 537UDM_AppInfo.rc resource.rc
	$(WINDRES) -i 537UDM_AppInfo.rc --input-format=rc -o 537UDM_AppInfo.res -O coff  --include-dir ./resource
	@echo Build 537UDM_AppInfo.

