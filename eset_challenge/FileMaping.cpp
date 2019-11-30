#include "FileMaping.h"

FileMaping::FileMaping(std::string path)
{
	FileHandler fh(path);
	MapHandler mh(fh.getHandle());

	_SYSTEM_INFO  sysInfo;
	GetSystemInfo(&sysInfo);
	size_t granularity = sysInfo.dwAllocationGranularity;

	char * tmp_buffer = (char *)MapViewOfFile(mh.getHandle(), FILE_MAP_READ, 0, 0, 0);


	//size_t len = strlen(tmp_buffer)
	//char * buffer = new char[bufferSize + 1]{};
	//memcpy_s(&buffer[0], bufferSize, &tmp_buffer[0], bufferSize);
	//delete buffer;
}


FileMaping::~FileMaping()
{
}





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




//zakres z jakie tworzymy
MapView::MapView(HANDLE hMMap)
{
	mapView = (char *)MapViewOfFile(hMMap, FILE_MAP_READ, 0, 0, 0);
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
