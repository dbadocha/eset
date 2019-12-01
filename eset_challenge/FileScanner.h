#pragma once
#include <string>
#include <iostream>
#include <list>
#include "FoundStringData.h"
#include "FileReader.h"


struct partMatch
{
	fileSize_t pageOffset = 0;
	fileSize_t charToCheckPos = 0;
	FoundStringData * stringData = NULL;
};


struct PageScannerData
{
	std::list <partMatch> partialMatch;
	std::list <partMatch> pagePos;
};


class PageScanner
{
private:
	PageScannerData &data;
	PageData &page;
	const std::string stringToFind;
	
	void recalcPagePos();
	void scanList(char toCheck);
	void checkFirstChar(fileSize_t pagePos);
	void scanPage();

public:
	PageScanner(PageScannerData &data, PageData &page, std::string stringToFind);
	~PageScanner();
	void scanNextPage();
};


struct DataWriterData
{
	std::list <partMatch> withFileOffset;
	std::list <partMatch> withPrefix;
	std::list <partMatch> withSufix;
};


class FoundDataCreator
{
private:
	PageData &page;

public:
	FoundDataCreator(PageData &page);
	~FoundDataCreator();

	void writeFileOffset(std::list <partMatch> &input, std::list <partMatch> &output);
	void writePrefix(std::list <partMatch> &input, std::list <partMatch> &output);
	void writeSufix(std::list <partMatch> &input, std::list <FoundStringData*> &output);

	FoundStringData *fillPrefix(fileSize_t pagePos);
	FoundStringData *getSufix();
};