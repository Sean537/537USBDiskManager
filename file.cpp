/*
537 USB Disk Manager
Version 1.0 Beta

file.cpp

Copyright (C) 537 Studio. 2024. All rights reserved.
*/
#include "include/file.h"
#include <windows.h>
#include <cwchar>

bool IsExeFile(const std::wstring& fileName){
    size_t dotPos=fileName.rfind(L'.');
    if (dotPos==std::wstring::npos) return false; // 没有点，不是有效的文件名

    size_t exePos=fileName.rfind(L".exe",dotPos);
    return exePos!=std::wstring::npos && exePos==dotPos;
}

void ScanDirectoryForExe(const std::wstring& directoryPath,std::vector<std::wstring>& exeFiles){
	WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((directoryPath + L"/*").c_str(), &findFileData);
	
    if(hFind==INVALID_HANDLE_VALUE){
        DWORD dwError = GetLastError();
        if(dwError!=ERROR_FILE_NOT_FOUND){ // 如果不是没有找到文件的错误，打印错误信息
            std::wcerr<<L"FindFirstFile failed with error code: "<<dwError<<std::wendl;
        }
        return;
    }

    do{
        if(wcscpy(findFileData.cFileName,L".")==0 || wcscpy(findFileData.cFileName,L"..")==0){
            continue; // 跳过当前目录和上级目录
        }

        std::wstring fullPath=directoryPath+L"/"+findFileData.cFileName;
        if((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)!=0){
            // 是目录，递归调用ScanDirectoryForExe
            ScanDirectoryForExe(fullPath, exeFiles);
        }else if(IsExeFile(findFileData.cFileName)){
            // 是文件，检查是否是.exe文件
            exeFiles.push_back(fullPath);
        }
    }while(FindNextFile(hFind,&findFileData)!=0);

    FindClose(hFind);
}
