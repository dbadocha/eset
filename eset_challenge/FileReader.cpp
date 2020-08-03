#include "FileReader.h"


FileReader_ifstream::FileReader_ifstream(FileData &fileToSearch)
	: file(fileToSearch)
{
	std::string filePath = file.getFilePath();
	fileInput.open(filePath.c_str(), std::ifstream::in | std::ifstream::binary);

	if (!fileInput.is_open())
		throw std::runtime_error("Could not open file");
}


FileReader_ifstream::~FileReader_ifstream()
{
	fileInput.close();
}


fileSize_t FileReader_ifstream::length()
{
	fileSize_t mem = fileInput.tellg();
	fileInput.seekg(0, fileInput.end);
	fileSize_t length = fileInput.tellg();
	fileInput.seekg(mem);
	return length;
}


fileSize_t FileReader_ifstream::getFileOffset()
{
	return filePos;
}


std::string FileReader_ifstream::getFilePath()
{
	return file.getFilePath();
}


void FileReader_ifstream::resetGenerator()
{
	filePos = 0;
	fileInput.seekg(0);
}


Page FileReader_ifstream::fetchData(fileSize_t start, fileSize_t length)
{
	fileInput.seekg(start);
	if (fileInput.eof())
		throw std::runtime_error("EOF");

	std::shared_ptr<char[]> buffer(new char[length + 1]{});
	fileInput.read(buffer.get(), length);

	if (!fileInput.good())
		throw std::runtime_error("File reading error");

	return Page{buffer, length};
}


Page FileReader_ifstream::yield()
{
	filePos += pageLen;
	pageLen = this->length() - filePos;
	pageLen = pageSize < pageLen ? pageSize : pageLen;

	fileInput.seekg(filePos);
	return fetchData(filePos, pageLen);
}


bool FileReader_ifstream::isDone()
{
	if (filePos + pageLen >= this->length())
		return true;
	else
		return false;
}




std::unique_ptr<IFileReader> FileReaderFactory::getReader(FileData &fileData)
{
	_SYSTEM_INFO  sysInfo;
	GetSystemInfo(&sysInfo);
	fileSize_t granularity = static_cast<fileSize_t> (sysInfo.dwAllocationGranularity);

	if (fileData.getSize() > granularity * 10)
	{
		return std::unique_ptr<IFileReader>(new FileReader_ifstream(fileData));
	}
	else
		return std::unique_ptr<IFileReader>(new FileReader_ifstream(fileData));
}
