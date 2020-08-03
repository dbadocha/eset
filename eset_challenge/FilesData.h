#pragma once
#include <string>
#include <queue>
#include <iostream>

typedef long long fileSize_t;


class FileData
{
private:
	std::string fName;
	std::string	fPath;
	fileSize_t size;

public:
	FileData(std::string fName, std::string fPath, fileSize_t size);
	~FileData();

	std::string getName();
	std::string getPath();
	std::string getFilePath();
	fileSize_t getSize();
};



class FilesContainer
{
private:
	std::queue<FileData*> container;

public:
	FilesContainer();
	~FilesContainer();

	void push(FileData *newFile);
	void pop();
	bool empty();
	FileData* front();
	void clear();
	void print();
	FilesContainer &operator +=(FilesContainer &toAdd);
};