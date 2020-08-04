#pragma once

#include "File.h"

#include <vector>
#include <string>
#include <windows.h>

class ScanningMechanism
{
public:
	ScanningMechanism();
	~ScanningMechanism();
	bool findFirstFile(LPCSTR lpFileName);
	bool findNextFile();
	bool isFile();
	bool isDir();
	bool isValid();
	size_t getSize();
	std::string getFileName();
private:
	WIN32_FIND_DATAA _winFindData;
	HANDLE _hFind;
};


//drzewo katalogów
//skanowanie folderów
//funkcja nastêpny katalog

class DirScanner
{
public:
	DirScanner();
	~DirScanner();
	std::vector<File> scan(std::string path);
	std::vector<File> scan(std::string dir, std::string fileExt);
private:
	ScanningMechanism _scanner;
};