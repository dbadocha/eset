#pragma once
#include <string>
#include <list>
#include <iostream>


struct FoundStringData {
	std::string file = std::string("\03");
	std::string offset = std::string("\03");
	std::string prefix = std::string("\03");
	std::string sufix = std::string("\03");
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

