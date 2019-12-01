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


class MapView
{
private:
	char *mapView;
	size_t size;

public:
	//trzeba zakres
	//wyczyszczenie po otwarciu
	MapView(HANDLE hMMap, unsigned long long offset, size_t numberOfBytes);
	~MapView();
	const char *getDataPointer();
	size_t getSize();
};