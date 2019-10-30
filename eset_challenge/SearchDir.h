#pragma once
#include <string>
#include <windows.h>
#include "FilesListContainer.h"
#include <tchar.h> 

class SearchDir
{
public:
	SearchDir(FilesListContainer &queueHandler);
	~SearchDir();
	void listDir(std::string dir);
	int pathCheck(std::string &path);
	void inputPathNorm(std::string &path);

private:
	FilesListContainer &queueHandler;
	const unsigned int bitOffset = sizeof(DWORD) * 8;
	
};