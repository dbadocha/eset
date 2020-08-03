#include <list>
#include <set>
#include <unordered_map>
#include "FoundStringData.h"
#include "FileReader.h"
#pragma once


class PageStringConcat
{
public:
	void concat(std::string &inOut, Page& page, unsigned int overlap);
	std::string concat_cpy(std::string &in, Page& page, unsigned int overlap);
};


class IPageScanner
{
protected:
	const std::string pattern;

public:
	IPageScanner(const std::string &pattern);
	virtual std::list <fileSize_t> scanNextPage(Page &nextPage) = 0;
};


struct PartMatch
{
	fileSize_t pageOffset = 0;
	size_t charToCheckPos = 0;
};


class PageScanner_Simple : public IPageScanner
{
private:
	std::list <PartMatch> partialMatch;
	std::list <fileSize_t> returnList;
	fileSize_t previousPageLen = 0;

	void recalcPageOffset();
	void scanList(const char &toCheck);
	void checkFirstChar(const char &toCheck, fileSize_t pagePos);

public:
	PageScanner_Simple(const std::string &pattern);
	~PageScanner_Simple();
	std::list <fileSize_t> scanNextPage(Page &nextPage);
};


class FiniteAutomata : public IPageScanner
{
private:
	std::string pattern;
	std::vector<std::unordered_map<char, int>> states;
	int currentState = 0;
	size_t pos = 0;
	void initStates();
	std::unordered_map<char, int> createMap(int stateNo);

public:
	FiniteAutomata(const std::string &pattern);
	~FiniteAutomata();
	std::list <fileSize_t> scanNextPage(Page &nextPage);
};


class PageScanner_BoyerMoore : public IPageScanner
{
private:
	std::string buffer{};
	std::set <char> setOfLetters{};
	std::string pattern;
	void initSet();

public:
	PageScanner_BoyerMoore(const std::string &pattern);
	~PageScanner_BoyerMoore();
	std::list <fileSize_t> scanNextPage(Page &nextPage);
};


class PageScanner_SysLib : public IPageScanner
{
private:
	unsigned int overlap = pattern.length();
	PageStringConcat concat;
	std::string page{};

public:
	PageScanner_SysLib(const std::string &pattern);
	~PageScanner_SysLib();
	std::list <fileSize_t> scanNextPage(Page &nextPage);
};