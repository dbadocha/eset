#include "FileReader.h"


PageData::PageData()
	: data(NULL), dataSize(0), pageSize(0), prevPageMem(std::string()), fileOffset(0)
{
}

PageData::~PageData()
{
}


void PageData::savePrevPageMem()
{
	if (data != NULL)
	{
	char buff[4];
	fileSize_t offset = pageSize - 4;
	strncpy_s(buff, 4, data + offset, 3);
	prevPageMem = buff;
	}
}


void PageData::setNextPage(const char *newData, fileSize_t newPageSize)
{
	savePrevPageMem();
	fileOffset += pageSize;
	pageSize = newPageSize;
	data = newData;
}


char const * PageData::getDataPointer()
{
	return data;
}


std::string PageData::getPageMem()
{
	return prevPageMem;
}


fileSize_t PageData::getPageSize()
{
	return pageSize;
}


fileSize_t PageData::getFileOffset()
{
	return fileOffset;
}






FileReader::FileReader()
{
}


FileReader::~FileReader()
{
}


FileReader_Simple::FileReader_Simple(FilesData &fileToSearch)
	: file(fileToSearch)
{
	openFile();
}


FileReader_Simple::~FileReader_Simple()
{
	closeFile();
}


void FileReader_Simple::openFile()
{
	std::string filePath = file.getFilePath();
	fileInput.open(filePath.c_str(), std::ifstream::in | std::ifstream::binary);

	if (!fileInput.is_open())
		throw std::runtime_error("Could not open file");
}


void FileReader_Simple::closeFile()
{
	fileInput.close();
}

fileSize_t FileReader_Simple::length()
{
	fileInput.seekg(0, fileInput.end);
	fileSize_t length = fileInput.tellg();
	fileInput.seekg(0, fileInput.beg);
	return length;
}

//int FileReader_Simple::fetchData(PageData page)
//{
//	fileInput.read(page.data, page.size);
//	std::cout << page.data << std::endl;
//
//	if (!fileInput.goodbit)
//		return -1;
//	else if (fileInput.end) //////////////////////////////////////////test eof
//		return 1;
//	return 0;
//}