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


//skanowanie folderów
//funkcja nastêpny katalog

class ScannerFilter
{
public:
	ScannerFilter() = default;
	virtual ~ScannerFilter() = default;
	virtual bool check(ScanningMechanism &scanner) = 0;
};

class ScannerFilter_Dir : public ScannerFilter
{
public:
	ScannerFilter_Dir() = default;
	~ScannerFilter_Dir() = default;
	bool check(ScanningMechanism & scanner);
};

class ScannerFilter_File : public ScannerFilter
{
public:
	ScannerFilter_File(std::string extension);
	~ScannerFilter_File() = default;
	bool check(ScanningMechanism & scanner);
private:
	std::string _extension;
};

class DirScanner
{
public:
	DirScanner();
	~DirScanner();
	std::vector<File> scan(std::string path);
	std::vector<File> scan(std::string dir, ScannerFilter &filter);
private:
	ScanningMechanism _scanner;
};