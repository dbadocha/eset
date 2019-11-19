#include "Compare.h"



SearchFile::SearchFile(FilesData &fileToRead)
	: fileToRead(fileToRead)
{
}


SearchFile::~SearchFile()
{
}

int SearchFile::searchFile()
{
	file = new FileReader_Simple(fileToRead);

	//file->fetchData(toSearch);
	return 0;
}



SearchPage::SearchPage(std::list <matchInfo> &matchList, std::string &toFind)
	: matchList(matchList), toFind(toFind)
{
}


SearchPage::~SearchPage()
{
}


void SearchPage::fillOffset(matchInfo &toFill)
{
	toFill.stringData.offset = std::to_string(fileOffset + toFill.pageOffset);
}


void SearchPage::fillPrefix(matchInfo &toFill)
{
	fileSize_t prefixOffset = toFill.pageOffset - 3;
	int prefixLen = 3;

	if (prefixOffset < 0)
	{
		fileSize_t memPos = prefixMem.length() - abs(prefixOffset);
		toFill.stringData.prefix = prefixMem.substr(memPos, memPos + 1);
		prefixLen += static_cast<int>(prefixOffset);
		prefixOffset = 0;
	}

	char buff[4];
	strncpy_s(buff, prefixLen, toSearch + prefixOffset, prefixLen);

	toFill.stringData.prefix += buff;
}


void SearchPage::saveMatchInfo()
{
	for (it = partialMatch.begin(); it != partialMatch.end(); ++it)
	{
		fillOffset(*it);
		fillPrefix(*it);
	}
}


void SearchPage::nextPage(char * toSearch, fileSize_t len)
{
	this->toSearch = toSearch;
	this->fileOffset += pageSize;
	pageSize = len;
}


void SearchPage::addNewMatch(fileSize_t pageOffset)
{
	matchInfo tmp{};
	tmp.pageOffset = pageOffset;
	tmp.charToCheckPos = 1;
	partialMatch.push_back(tmp);
}


int SearchPage::compare(char toCheck)
{
	int ret = 0;
	for (it = partialMatch.begin(); it != partialMatch.end(); ++it)
	{
		fileSize_t pos = it->charToCheckPos;
		char tmp = toFind[pos];
		if (tmp != toCheck)
		{
			it = partialMatch.erase(it);
			continue;
		}

		++it->charToCheckPos;
		if (it->charToCheckPos == toFind.length())
		{
			matchList.push_back(*it);
			it = partialMatch.erase(it);
			ret = 1;
		}
	}
	return ret;
}

int SearchPage::startComparing()
{
	for (int i = 0; i < pageSize; ++i)
	{

	}
	return 0;
}


