#pragma once
#include <windows.h>
#include <string>
#include "FoundFilesGenerator.h"


class FileHandler
{
private:
	HANDLE hFile;

public:
	FileHandler(std::string path);
	~FileHandler();
	HANDLE getHandle();
};


class MapHandler
{
private:
	HANDLE hMMap;

public:
	MapHandler(HANDLE hFile);
	~MapHandler();
	HANDLE getHandle();
	bool isValid();
};


class MapViewer
{
private:
	char *mapView;
	size_t size;

public:
	//trzeba zakres
	//wyczyszczenie po otwarciu
	MapViewer(HANDLE hMMap, fileSize_t offset, size_t numberOfBytes);
	~MapViewer();
	const char *getDataPointer();
	size_t getSize();
};


//D³ugoœæ pliku
//
//LARGE_INTEGER qwFileSize;
//qwFileSize.QuadPart = 0;
//GetFileSizeEx(hFile, &qwFileSize);
//std::cout << qwFileSize.QuadPart << "\n";