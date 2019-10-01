#include "FileMaping.h"

FileMaping::FileMaping(std::string path)
{
	createToReadHandler(path);
	mapFileToRead(hFile);
	//createView(hMMap);

	_SYSTEM_INFO  sysInfo;
	GetSystemInfo(&sysInfo);
	int bufferSize = sysInfo.dwAllocationGranularity;

	//int bufferSize = 10;
	char * buffer = new char[bufferSize];
	std::cout << sysInfo.dwAllocationGranularity;
	char * tmp_buffer = (char *)MapViewOfFile(hMMap, FILE_MAP_READ, 0, sysInfo.dwAllocationGranularity, sysInfo.dwPageSize*2);

	memcpy(&buffer[0], &tmp_buffer[0], bufferSize);
	std::cout << buffer;
	//tmp_buffer;

	UnmapViewOfFile(tmp_buffer);
	CloseHandle(hMMap);
	CloseHandle(hFile);
}


FileMaping::~FileMaping()
{
}

HANDLE FileMaping::createToReadHandler(std::string path)
{
	const char * c_path = path.c_str();
	hFile = CreateFile(c_path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_READONLY | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	return hFile;
}

HANDLE FileMaping::mapFileToRead(HANDLE fFile)
{
	hMMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
	if (hMMap == INVALID_HANDLE_VALUE)
		std::cout << "NOPE";
	return hMMap;
}

LPVOID FileMaping::createView(HANDLE hMMap)
{
	fileView = MapViewOfFile(hMMap, FILE_MAP_READ, 0, 0, 0);
	return fileView;
}

//VirtualQuery