#include "FoundStringData.h"



FoundStringDataContainer::FoundStringDataContainer()
{
}


FoundStringDataContainer::~FoundStringDataContainer()
{
}

void FoundStringDataContainer::push(FoundStringData * foundData)
{
	container.push_back(foundData);
}

FoundStringData * FoundStringDataContainer::get()
{
	return container.front();
}

FoundStringData * FoundStringDataContainer::getNext()
{
	++it;
	if (it == container.end())
		return *it;
	else
		return NULL;
}

void FoundStringDataContainer::print()
{
	for (it = container.begin(); it == container.end(); ++it)
		std::cout << (*it)->file << std::endl;
}

void FoundStringDataContainer::pop()
{
	container.pop_front();
}

bool FoundStringDataContainer::empty()
{
	return container.empty();
}

void FoundStringDataContainer::clear()
{
	container.clear();
}


FoundStringDataContainer &FoundStringDataContainer::operator+=(FoundStringDataContainer &toAdd)
{
	for (int i = 0; i < toAdd.container.size(); ++i)
	{
		this->container.push_back(toAdd.container.front());
		toAdd.pop();
	}
	return *this;
}