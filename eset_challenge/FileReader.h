#pragma once
#include <string>
#include <fstream>
#include <windows.h>
#include "FilesData.h"
#include "FoundStringData.h"

struct Page
{
	std::shared_ptr<const char[]> data;
	fileSize_t size;
};


class IFileReader_Generator
{
public:
	virtual void resetGenerator() = 0;
	virtual Page yield() = 0;
	virtual bool isDone() = 0;
	virtual fileSize_t getFileOffset() = 0;
	virtual std::string getFilePath() = 0;
};


class IFileReader
{
public:
	virtual Page fetchData(fileSize_t start, fileSize_t end) = 0;
	virtual fileSize_t length() = 0;
	virtual std::string getFilePath() = 0;
};


class FileReader_ifstream : public IFileReader, public IFileReader_Generator
{
private:
	const fileSize_t pageSize = 2 << 15;
	FileData &file;
	std::ifstream fileInput;
	fileSize_t filePos = 0, pageLen = 0;

public:
	FileReader_ifstream(FileData &fileToRead);
	~FileReader_ifstream();

	void resetGenerator();
	Page fetchData(fileSize_t start, fileSize_t end);
	Page yield();
	bool isDone();
	fileSize_t length();
	fileSize_t getFileOffset();
	std::string getFilePath();
};


//class FileReader_mmap : public IFileReader, public IFileReader_Generator
//{
//private:
//	FileHandler fileHandler;
//	MapHandler mapHandler;
//	MapView mapView;
//	fileSize_t filePos = 0;
//
//public:
//	FileReader_mmap(FileData &fileToRead);
//	~FileReader_mmap();
//
//	Page fetchData(fileSize_t start, fileSize_t end);
//	void resetGenerator();
//	Page yield();
//	bool isDone();
//	fileSize_t length();
//	fileSize_t getFileOffset();
//	std::string getFilePath();
//};


class FileReaderFactory
{
public:
	static std::unique_ptr<IFileReader> getReader(FileData &fileData);
};