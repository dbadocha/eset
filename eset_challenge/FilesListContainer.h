#pragma once
#include <queue>
#include <string>
#include <iostream>
#include "FileData.h"

class FilesListContainer : public std::queue<FileData>
{

public:
	FilesListContainer();
	~FilesListContainer();

	void push(std::string fileName, std::string filePath, unsigned long long size);
	void print();
};