#pragma once
#include <vector>
#include <string>
#include "FilesQueue.h"

struct FoundString {
	std::string file;
	std::string offset;
	std::string prefix;
	std::string sufix;
};

class SearchManager
{
public:
	SearchManager(FilesQueue &fQueue);
	~SearchManager();
private:
	FilesQueue &queueHandler;
	std::vector<FoundString> foundStrings;
	void simpleSearch();
};