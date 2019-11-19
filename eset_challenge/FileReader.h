#pragma once
#include <string>
#include <fstream>
#include "FilesData.h"
#include "FoundStringData.h"



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

	int fetchData(char * data, long size);
	fileSize_t length();

};

