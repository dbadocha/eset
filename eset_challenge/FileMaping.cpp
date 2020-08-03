#include "FileMaping.h"


FileHandler::FileHandler(std::string path)
{
	hFile = CreateFile(Path::normalizePath(path).c_str()
		, GENERIC_READ
		, FILE_SHARE_READ
		, NULL
		, OPEN_EXISTING
		, FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_READONLY
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





MapViewer::MapViewer(HANDLE hMMap, fileSize_t offset, size_t numberOfBytes)
{
	DWORD offsetHigh, offsetLow;
	offsetLow |= offset;
	offsetHigh |= offset >> 32;
 	mapView = (char *)MapViewOfFile(hMMap, FILE_MAP_READ, offsetHigh, offsetLow, numberOfBytes);
}


MapViewer::~MapViewer()
{
	UnmapViewOfFile(mapView);
}


const char * MapViewer::getDataPointer()
{
	return mapView;
}


size_t MapViewer::getSize()
{
	return strlen(mapView);
}
