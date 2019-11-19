#include "FileReader.h"



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

int FileReader_Simple::fetchData(char * data, long size)
{
	fileInput.read(data, size);
	std::cout << data << std::endl;

	if (!fileInput.goodbit)
		return -1;
	if (fileInput.end) //////////////////////////////////////////test eof
		return 1;
	return 0;
}