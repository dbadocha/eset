#include "FileScanner.h"


void PageToFileOffset::convert(std::list<fileSize_t> &pageSearchResult, fileSize_t fileOffset)
{
	std::list<fileSize_t>::iterator it;
	for (it = pageSearchResult.begin(); it != pageSearchResult.end(); ++it)
	{
		*it = *it + fileOffset;
	}
}

std::list<fileSize_t> PageToFileOffset::convert_cpy(std::list<fileSize_t>& pageSearchResult, fileSize_t fileOffset)
{
	std::list<fileSize_t> returnList;
	for (auto it : pageSearchResult)
	{
		returnList.push_front(it + fileOffset);
	}
	return returnList;
}


FileScanner::FileScanner(IFileReader_Generator &fileReader)
	: fileReader(fileReader)
{
}


FileScanner::~FileScanner()
{
	delete(pageScanner);
}


void FileScanner::initDataList(std::string &pattern)
{
	returnList.pattern = pattern;
	returnList.path = fileReader.getFilePath();
	returnList.patternFilePos = {};
}


void FileScanner::initPageScanner(std::string &pattern)
{
	//pageScanner = new PageScanner_SysLib(pattern);
}


void FileScanner::scanFile(std::string &pattern)
{
	initDataList(pattern);
	initPageScanner(pattern);

	while (!fileReader.isDone())
	{
		Page tmpPage = fileReader.yield();
		std::list <fileSize_t> tmpList = pageScanner->scanNextPage(tmpPage);
		PageToFileOffset::convert(tmpList, fileReader.getFileOffset());
		returnList.patternFilePos.merge(tmpList);
		tmpList.clear();
	}
	std::cout << returnList.patternFilePos.size() << "\n";
}