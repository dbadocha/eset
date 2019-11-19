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


class FoundFilesGenerator
{
private:
	const fileSize_t bitOffset = sizeof(DWORD) * 8;

protected:
	std::list<std::string> pathList;
	std::string pathMem;
	WIN32_FIND_DATAA winFindData;
	HANDLE hFind;

	bool isFile();
	bool isDir();
	bool isValid();

public:
	FoundFilesGenerator(std::string path);
	~FoundFilesGenerator();
	std::string getPath();
	fileSize_t getSize();
	virtual FilesData *findNext() = 0;
};


class FoundFilesGenerator_Dir : public FoundFilesGenerator
{
private:
	const std::string extention;
	bool checkExt();

public:
	FoundFilesGenerator_Dir(std::string path, std::string range = "*");
	~FoundFilesGenerator_Dir();
	FilesData *findNext();
};


class FoundFilesGenerator_File : public FoundFilesGenerator
{
public:
	FoundFilesGenerator_File(std::string path);
	~FoundFilesGenerator_File();
	FilesData *findNext();
};
