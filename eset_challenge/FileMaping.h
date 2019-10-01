#pragma once
#include <windows.h>
#include <string>
#include <iostream>
#include <debugapi.h>
#include <fstream>

class FileMaping
{
public:
	FileMaping(std::string path);
	~FileMaping();

private:
	HANDLE hFile;
	HANDLE mapFileToRead(HANDLE fFile);
	HANDLE createToReadHandler(std::string path);
	LPVOID createView(HANDLE hMap);
	HANDLE fFile;
	HANDLE hMMap;
	LPVOID fileView;
};