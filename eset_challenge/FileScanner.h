#pragma once
#include <string>
#include <iostream>
#include <memory>
#include "FoundStringData.h"
#include "FileReader.h"
#include "PageScanner.h"


struct SearchData
{
	std::string pattern;
	std::string path;
	std::list <fileSize_t> patternFilePos;
};


class PageToFileOffset
{
public:
	static void convert(std::list <fileSize_t> &pageSearchResult, fileSize_t fileOffset);
	static std::list <fileSize_t> convert_cpy(std::list <fileSize_t> &pageSearchResult, fileSize_t fileOffset);
};


class FileScanner
{
private:
	IFileReader_Generator &fileReader;
	IPageScanner *pageScanner;
	SearchData returnList;
	void initDataList(std::string &pattern);
	void initPageScanner(std::string &pattern);

public:
	FileScanner(IFileReader_Generator &fileReader);
	~FileScanner();
	void scanFile(std::string &pattern);
	std::list <fileSize_t> &getResult();
};


//class PatternDataCollector
//{
//private:
//	IFileReader &fileReader;
//	std::list <SearchData> retData;
//
//public:
//	PatternDataCollector(IFileReader &fileReader);
//	virtual std::list <SearchData> &getResult() = 0;
//};
//
//
//
//class FileScanningManager
//{
//private:
//	FileData &fileData;
//	FoundStringDataContainer retData;
//	IFileReader *fileReader;
//	FileScanner *fileScanner;
//	PatternDataCollector *dataCollector;
//	void initReader();
//	void initScanner();
//	void initConnector();
//	void scanFile();
//	void collectData();
//
//public:
//	FileScanningManager(FileData &fileData, FoundStringDataContainer &retData);
//	~FileScanningManager();
//	void scan(std::string pattern);
//	FoundStringDataContainer &getData();
//};
