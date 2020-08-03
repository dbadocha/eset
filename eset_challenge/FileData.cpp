#include "FilesData.h"

FileData::FileData(std::string fName, std::string fPath, fileSize_t size)
	: fName(fName), fPath(fPath), size(size)
{
}


FileData::~FileData()
{
}


std::string FileData::getName()
{
	return fName;
}


std::string FileData::getPath()
{
	return fPath;
}


std::string FileData::getFilePath()
{
	return fPath + "\\" + fName;
}


fileSize_t FileData::getSize()
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


void FilesContainer::push(FileData *newFile)
{
	container.push(newFile);
}


void FilesContainer::pop()
{
	container.pop();
}


FileData* FilesContainer::front()
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
