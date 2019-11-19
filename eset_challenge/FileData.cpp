#include "FilesData.h"

FilesData::FilesData(std::string fName, std::string fPath, fileSize_t size)
	: fName(fName), fPath(fPath), size(size)
{
}


FilesData::~FilesData()
{
}


std::string FilesData::getName()
{
	return fName;
}


std::string FilesData::getPath()
{
	return fPath;
}


std::string FilesData::getFilePath()
{
	return fPath + "\\" + fName;
}


fileSize_t FilesData::getSize()
{
	return size;
}





FilesContainer::FilesContainer()
{
}


FilesContainer::~FilesContainer()
{
	clear();
}


void FilesContainer::push(FilesData *newFile)
{
	container.push(newFile);
}


void FilesContainer::pop()
{
	container.pop();
}


FilesData* FilesContainer::front()
{
	return container.front();
}


void FilesContainer::clear()
{
	while (!container.empty())
	{
		delete container.front();
		container.pop();
	}
}


void FilesContainer::print()
{
	while (!container.empty()) {
		std::cout << front()->getFilePath() << "\n";
		pop();
	}
}

FilesContainer& FilesContainer::operator+=(FilesContainer &toAdd)
{
	for (int i = 0; i < toAdd.container.size(); ++i)
	{
		this->container.push(toAdd.container.front());
		toAdd.container.pop();
	}
	return *this;
}


bool FilesContainer::empty()
{
	return container.empty();
}
