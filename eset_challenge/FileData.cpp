#include "FileData.h"

FileData::FileData(std::string fName, std::string fPath, unsigned long long size)
	: fName(fName), fPath(fPath), size(size)
{
}


FileData::~FileData()
{
}

std::string FileData::fileName()
{
	return this->fName;
}

std::string FileData::getFilePath()
{
	return fPath + "\\" + fName;
}
