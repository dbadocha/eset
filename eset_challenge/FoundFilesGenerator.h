#pragma once
#include <string>
#include <windows.h>
#include <tchar.h> 
#include <algorithm>
#include <list>

#include "FilesData.h"


class Path
{
public:
	static std::string normalizePath(std::string path);
	static std::string moveDown(std::string path);
	static std::string moveUp(std::string path, std::string dir);
	static bool isFile(std::string path);
};

/*
Brakuje wyrzucania wyników w momencie podania bezpoœredniej œcie¿ki do pliku
*/
class FoundFilesGenerator
{
private:
	const fileSize_t bitOffset = sizeof(DWORD) * 8;
	const std::string extention;
	WIN32_FIND_DATAA winFindData;
	HANDLE hFind;
	std::list<std::string> pathList;
	std::string pathMem;

	bool _isFile();
	bool _isDir();
	bool _isValid();
	bool _checkExt();

public:
	FoundFilesGenerator(std::string path, std::string range = "*");
	~FoundFilesGenerator();
	std::string getPath();
	fileSize_t getSize();
	FilesData *findNext();
};
