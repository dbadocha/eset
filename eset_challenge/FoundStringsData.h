#pragma once
#include <string>
#include <list>


struct FoundString {
	std::string file;
	std::string offset;
	std::string prefix;
	std::string sufix;
};

class FoundStringsData
{
private:
	std::list<FoundString> container;

public:
	FoundStringsData();
	~FoundStringsData();

	FoundString pop();
	void push(FoundString foundData);
	void print();

	FoundString operator+= (FoundString& listToAdd);
};

