#include "PageScanner.h"


void PageStringConcat::concat(std::string &inOut, Page &page, unsigned int overlap)
{
	inOut = inOut.substr(inOut.size() - overlap, overlap);
	inOut += std::string(page.data.get(), page.size);
}


std::string PageStringConcat::concat_cpy(std::string &in, Page &page, unsigned int overlap)
{
	std::string ret = in.substr(in.size() - overlap, overlap);
	ret += std::string(page.data.get(), page.size);
	return ret;
}





IPageScanner::IPageScanner(const std::string & pattern)
	: pattern(pattern)
{
}





PageScanner_Simple::PageScanner_Simple(const std::string &pattern)
	: IPageScanner(pattern)
{
}


PageScanner_Simple::~PageScanner_Simple()
{
}


std::list <fileSize_t> PageScanner_Simple::scanNextPage(Page &nextPage)
{
	recalcPageOffset();
	previousPageLen = nextPage.size;
	for (fileSize_t pagePos = 0; pagePos < nextPage.size; ++pagePos)
	{
		if (partialMatch.size() > 0)
			scanList(nextPage.data[pagePos]);
		checkFirstChar(nextPage.data[pagePos], pagePos);
	}
	return returnList;
}


void PageScanner_Simple::recalcPageOffset()
{
	std::list <PartMatch>::iterator it;
	for (it = partialMatch.begin(); it != partialMatch.end(); ++it)
	{
		it->pageOffset -= previousPageLen;
	}
}


void PageScanner_Simple::scanList(const char &toCheck)
{
	std::list <PartMatch>::iterator it;
	for (it = partialMatch.begin(); it != partialMatch.end(); ++it)
	{
		if (toCheck == pattern[it->charToCheckPos])
		{
			++(it->charToCheckPos);

			if (it->charToCheckPos == pattern.length())
			{
				fileSize_t stringFilePosition = it->pageOffset;
				returnList.push_back(stringFilePosition);
				it = partialMatch.erase(it);
			}
		}
		else
			it = partialMatch.erase(it);

		if (partialMatch.empty())
			break;
	}

}


void PageScanner_Simple::checkFirstChar(const char &toCheck, fileSize_t pagePos)
{
	if (toCheck == pattern[0])
	{
		PartMatch firstHit{ pagePos , 1 };
		partialMatch.push_back(firstHit);
	}
}





FiniteAutomata::FiniteAutomata(const std::string &pattern)
	: IPageScanner(pattern)
{
	initStates();
}

FiniteAutomata::~FiniteAutomata()
{
}


void FiniteAutomata::initStates()
{
	for (int i = 0; i < pattern.length(); ++i)
	{
		states.push_back(createMap(i));
	}
}


std::unordered_map<char, int> FiniteAutomata::createMap(int stateNo)
{
	std::unordered_map<char, int> retMap{};
	retMap[pattern[0]] = 1;
	if (stateNo != pattern.length())
		retMap[pattern[stateNo]] = stateNo + 1;

	for (int i = 1; i <= stateNo; ++i)
	{
		if (pattern.substr(0, i) == pattern.substr(stateNo - i, i))
			retMap[pattern[i]] = i + 1;
	}
	return retMap;
}


std::list <fileSize_t> FiniteAutomata::scanNextPage(Page &nextPage)
{
	std::list <fileSize_t> returnList;
	for (size_t pagePos = 0; pagePos < nextPage.size; ++pagePos)
	{
		auto search = states[currentState].find(nextPage.data[pagePos]);
		if (search != states[currentState].end())
		{
			pos += (currentState - search->second) + 1;
			currentState = search->second;

			if (currentState == pattern.length())
			{
				returnList.push_back(pagePos);
				currentState = 0;
			}
		}
		else
		{
			pos += currentState + 1;
			currentState = 0;
		}
	}
	return returnList;
}





PageScanner_BoyerMoore::PageScanner_BoyerMoore(const std::string &pattern)
	: IPageScanner(pattern)
{
	initSet();
}


PageScanner_BoyerMoore::~PageScanner_BoyerMoore()
{
}


void PageScanner_BoyerMoore::initSet()
{
	for (auto it : pattern)
	{
		setOfLetters.insert(it);
	}
}



std::list <fileSize_t> PageScanner_BoyerMoore::scanNextPage(Page &nextPage)
{
	std::list <fileSize_t> returnList{};
	const size_t patternLen = pattern.length();
	size_t Pos = patternLen - 1;
	const auto end = setOfLetters.end();
	const auto ptr = nextPage.data.get();

	while (Pos < nextPage.size)
	{
		if (setOfLetters.find(ptr[Pos]) == end)
			Pos += patternLen;
		else
		{
			int i = patternLen - 1;
			size_t tmpPos = Pos;
			while (i >= 0)
			{
				if (nextPage.data.get()[tmpPos] == pattern[i])
				{
					if (i == 0)
					{
						returnList.push_back(tmpPos);
						++Pos;
						break;
					}
					else
					{
						--tmpPos;
						--i;
					}
				}
				else
				{
					++Pos;
					break;
				}
			}
		}
	}
	return returnList;
}




PageScanner_SysLib::PageScanner_SysLib(const std::string &pattern)
	: IPageScanner(pattern)
{
	page = pattern;
	++page.at(0);
}


PageScanner_SysLib::~PageScanner_SysLib()
{
}


std::list<fileSize_t> PageScanner_SysLib::scanNextPage(Page &nextPage)
{
	std::list <fileSize_t> returnList{};
	concat.concat(page, nextPage, overlap);
	fileSize_t pagePos = 0;

	while (1)
	{
		pagePos = page.find(pattern, pagePos);
		if (pagePos >= page.length())
			break;
		returnList.push_back(pagePos - overlap);
		++pagePos;
	}
	return returnList;
}
