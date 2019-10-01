#pragma once
#include <string>

class FileData
{
public:
	FileData(std::string fName, std::string fPath, unsigned long long size);
	~FileData();

	std::string fileName();
	std::string getFilePath();
	

private:
	std::string fName;
	std::string	fPath;
	int size;
};