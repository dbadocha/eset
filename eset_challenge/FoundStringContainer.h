#pragma once
#include <string>
#include <list>

struct FoundString {
	std::string file;
	std::string offset;
	std::string prefix;
	std::string sufix;
};

class FoundStringContainer
{
private:
	std::list<FoundString> container;

public:
	FoundStringContainer();
	~FoundStringContainer();

	FoundString pop();
	void push(FoundString foundData);
	void print();

	FoundString operator+= (FoundString& listToAdd);
};

