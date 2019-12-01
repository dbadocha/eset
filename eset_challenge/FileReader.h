#pragma once
#include <string>
#include <fstream>
#include "FilesData.h"
#include "FoundStringData.h"

class PageData
{
private:
	const char *data = NULL;
	fileSize_t dataSize;
	std::string prevPageMem;
	fileSize_t pageSize;
	fileSize_t fileOffset;

	void savePrevPageMem();

public:
	PageData();
	~PageData();
	void setNextPage(const char *newData, fileSize_t newPageSize);
	char const * getDataPointer();
	std::string getPageMem();
	fileSize_t getPageSize();
	fileSize_t getFileOffset();
};


class FileReader
{
public:
	FileReader();
	~FileReader();

	virtual int fetchData(char * data, long size) = 0;
	virtual fileSize_t length() = 0;
};


class FileReader_Simple : public FileReader
{
private:
	FilesData &file;
	std::ifstream fileInput;
	void openFile();
	void closeFile();

public:
	FileReader_Simple(FilesData &fileToRead);
	~FileReader_Simple();

	int fetchData(PageData data);
	fileSize_t length();
};

