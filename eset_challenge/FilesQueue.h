#pragma once
#include <queue>
#include "FileData.h"
#include <string>
#include <iostream>

class FilesQueue : public std::queue<FileData>
{
public:
	FilesQueue();
	~FilesQueue();
	void push(std::string fileName, std::string filePath, unsigned long long size);
	void print();
};