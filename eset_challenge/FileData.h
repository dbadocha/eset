#pragma once
#include <string>

class FileData
{
private:
	std::string fName;
	std::string	fPath;
	int size;

public:
	FileData(std::string fName, std::string fPath, unsigned long long size);
	~FileData();

	std::string getFileName();
	std::string getFilePath();
	unsigned long long getSize();
};