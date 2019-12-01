#include "FileMaping.h"


FileHandler::FileHandler(std::string path)
{
	hFile = CreateFile(Path::normalizePath(path).c_str()
		, GENERIC_READ
		, FILE_SHARE_READ
		, NULL
		, OPEN_EXISTING
		, FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_READONLY | FILE_FLAG_SEQUENTIAL_SCAN
		, NULL);
}


FileHandler::~FileHandler()
{
	CloseHandle(hFile);
}


HANDLE FileHandler::getHandle()
{
	return hFile;
}





MapHandler::MapHandler(HANDLE hFile)
{
	hMMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
}


MapHandler::~MapHandler()
{
	CloseHandle(hMMap);
}


HANDLE MapHandler::getHandle()
{
	return hMMap;
}


bool MapHandler::isValid()
{
	if (hMMap != INVALID_HANDLE_VALUE)
		return true;
}





MapView::MapView(HANDLE hMMap, unsigned long long offset, size_t numberOfBytes)
{
	DWORD offsetHigh, offsetLow;
	offsetLow |= offset;
	offsetHigh |= offset >> 32;
 	mapView = (char *)MapViewOfFile(hMMap, FILE_MAP_READ, offsetHigh, offsetLow, numberOfBytes);
}


MapView::~MapView()
{
	UnmapViewOfFile(mapView);
}


const char * MapView::getDataPointer()
{
	return mapView;
}


size_t MapView::getSize()
{
	return strlen(mapView);
}
