/*
537 USB Disk Manager
Version 1.0 Beta

file.cpp

Copyright (C) 537 Studio. 2024. All rights reserved.
*/
#include "include/file.h"
#include <windows.h>

bool IsExeFile(const std::string& fileName){
    size_t dotPos=fileName.rfind('.');
    if (dotPos==std::string::npos) return false; // û�е㣬������Ч���ļ���

    size_t exePos=fileName.rfind(".exe",dotPos);
    return exePos!=std::string::npos && exePos==dotPos;
}

void ScanDirectoryForExe(const std::string& directoryPath,std::vector<std::string>& exeFiles){
	WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((directoryPath + "/*").c_str(), &findFileData);
	
    if(hFind==INVALID_HANDLE_VALUE){
        DWORD dwError = GetLastError();
        if(dwError!=ERROR_FILE_NOT_FOUND){ // �������û���ҵ��ļ��Ĵ��󣬴�ӡ������Ϣ
            std::cerr<<"FindFirstFile failed with error code: "<<dwError<<std::endl;
        }
        return;
    }

    do{
        if(strcmp(findFileData.cFileName,".")==0 || strcmp(findFileData.cFileName,"..")==0){
            continue; // ������ǰĿ¼���ϼ�Ŀ¼
        }

        std::string fullPath=directoryPath+"/"+findFileData.cFileName;
        if((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)!=0){
            // ��Ŀ¼���ݹ����ScanDirectoryForExe
            ScanDirectoryForExe(fullPath, exeFiles);
        }else if(IsExeFile(findFileData.cFileName)){
            // ���ļ�������Ƿ���.exe�ļ�
            exeFiles.push_back(fullPath);
        }
    }while(FindNextFile(hFind,&findFileData)!=0);

    FindClose(hFind);
}
