#pragma once
#include <string>
#include <windows.h>
#include "FilesQueue.h"
#include <tchar.h> 

class SearchDir
{
public:
	SearchDir(FilesQueue &queueHandler);
	~SearchDir();
	void listDir(std::string dir);
	int pathCheck(std::string &path);
	void inputPathNorm(std::string &path);

private:
	FilesQueue &queueHandler;
	const unsigned int bitOffset = sizeof(DWORD) * 8;
	
};