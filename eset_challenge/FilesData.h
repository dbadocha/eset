#pragma once
#include <string>
#include <queue>
#include <iostream>

typedef long long fileSize_t;



class FilesData
{
private:
	std::string fName;
	std::string	fPath;
	fileSize_t size;

public:
	FilesData(std::string fName, std::string fPath, fileSize_t size);
	~FilesData();

	std::string getName();
	std::string getPath();
	std::string getFilePath();
	fileSize_t getSize();
};



class FilesContainer 
{
private:
	std::queue<FilesData*> container;

public:
	FilesContainer();
	~FilesContainer();

	void push(FilesData *newFile);
	void pop();
	bool empty();
	FilesData* front();
	void clear();
	void print();
	FilesContainer &operator +=(FilesContainer &toAdd);
};