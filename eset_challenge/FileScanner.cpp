#include "FileScanner.h"



PageScanner::PageScanner(PageScannerData &data, PageData &page, std::string stringToFind)
	:data(data), page(page), stringToFind(stringToFind)
{
}


PageScanner::~PageScanner()
{
}


void PageScanner::scanNextPage()
{
	recalcPagePos();
	scanPage();
}


void PageScanner::scanPage()
{
	const char *pageData = page.getDataPointer();
	for (fileSize_t pagePos = 0; pagePos < page.getPageSize(); ++pagePos)
	{
		scanList(pageData[pagePos]);
		checkFirstChar(pagePos);
	}
}


void PageScanner::scanList(char toCheck)
{
	std::list <partMatch>::iterator it;
	for (it = data.partialMatch.begin(); it != data.partialMatch.end(); ++it)
	{
		if (toCheck == stringToFind[it->charToCheckPos])
		{
			++(it->charToCheckPos);

			if (it->charToCheckPos == stringToFind.length())
			{
				data.pagePos.push_back(*it);
				it = data.partialMatch.erase(it);
			}
		}
		else
			it = data.partialMatch.erase(it);

		if (data.partialMatch.empty())
			break;
	}
}


void PageScanner::checkFirstChar(fileSize_t pagePos)
{
	if (page.getDataPointer()[pagePos] == stringToFind[0])
	{
		partMatch tmp{pagePos , 1};
		data.partialMatch.push_back(tmp);
	}
}


void PageScanner::recalcPagePos()
{
	std::list <partMatch>::iterator it;
	for (it = data.partialMatch.begin(); it != data.partialMatch.end(); ++it)
	{
		it->pageOffset -= page.getPageSize();
	}
}


MorphemeWriter::MorphemeWriter(PageData & page)
	: page(page)
{
}

MorphemeWriter::~MorphemeWriter()
{
}

//FoundStringData *MorphemeWriter::fillPrefix(fileSize_t pagePos)
//{
//	FoundStringData *ret = new FoundStringData();
//
//	fileSize_t prefixPos = pagePos - 3;
//	int prefixLen = 3;
//
//	if (prefixPos < 0)
//	{
//		fileSize_t memPos = page.getPageMem.length() - abs(prefixPos);
//
//		toFill.stringData.prefix = page.prevMem.substr(memPos, memPos + 1);
//		prefixLen += static_cast<int>(prefixPos);
//		prefixPos = 0;
//	}
//
//	char buff[4];
//	strncpy_s(buff, prefixLen, pageToSearch + prefixPos, prefixLen);
//
//	toFill.stringData.prefix += buff;
//}