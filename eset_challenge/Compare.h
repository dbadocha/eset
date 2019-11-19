#pragma once
#include <string>
#include <iostream>
#include <list>
#include "FoundStringsData.h"
#include "FileReader.h"

struct matchInfo
{
	FoundString stringData;
	fileSize_t pageOffset;
	fileSize_t charToCheckPos;
};


class SearchPage
{
private:
	std::list <matchInfo> &matchList;
	std::list <matchInfo> partialMatch;
	std::list <matchInfo>::iterator it;

	const std::string &toFind;
	std::string prefixMem;

	const char *toSearch;
	fileSize_t pageSize;
	fileSize_t fileOffset;

public:
	SearchPage(std::list <matchInfo> &matchList, std::string &toFind);
	~SearchPage();

	void fillOffset(matchInfo &toFill);
	void fillPrefix(matchInfo &toFill);

	void saveMatchInfo();
	void nextPage(char * toSearch, fileSize_t len);
	void addNewMatch(fileSize_t pageOffset);
	int compare(char toCheck);

	int startComparing();
};


class SearchFile
{
	std::list <matchInfo> matchList;
	const std::string *toFind;

	char toSearch[4096];
	FilesData &fileToRead;

	SearchPage *pageSearch;
	FileReader *file;

	fileSize_t pageSize = 0, fileSize = 0;

public:
	SearchFile(FilesData &fileToRead);
	~SearchFile();

	int searchFile();
	void loadNewPage();
};