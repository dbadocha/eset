#pragma once
#include <string>
#include <list>
#include <iostream>


struct FoundStringData {
	std::string file;
	std::string offset;
	std::string prefix;
	std::string sufix;
};


class FoundStringDataContainer
{
private:
	std::list<FoundStringData*> container;
	std::list<FoundStringData*>::iterator it;

public:
	FoundStringDataContainer();
	~FoundStringDataContainer();

	void push(FoundStringData *foundData);
	FoundStringData * get();
	FoundStringData * getNext();
	void print();
	void pop();
	bool empty();
	void clear();

	FoundStringDataContainer &operator+= (FoundStringDataContainer &toAdd);
};

