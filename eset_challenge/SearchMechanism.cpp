#include "SearchMechanism.h"

SearchMechanism::SearchMechanism()
{
}

SearchMechanism::~SearchMechanism()
{
}





SearchMechanism_Data::SearchMechanism_Data(FilesData &fileToRead)
	: fileToRead(fileToRead)
{
}

SearchMechanism_Data::~SearchMechanism_Data()
{
}





SearchMechanism_Simple::SearchMechanism_Simple(FilesData &fileToRead)
	: SearchMechanism_Data(fileToRead)
{
}


SearchMechanism_Simple::~SearchMechanism_Simple()
{
}


void SearchMechanism_Simple::search(std::string stringToFind)
{

}


FoundStringsData & SearchMechanism_Simple::getFoundData()
{
	return foundStringsBuff;
}





SearchMechanism_Advanced::SearchMechanism_Advanced(FilesData &fileToRead)
	: SearchMechanism_Data(fileToRead)
{

}


SearchMechanism_Advanced::~SearchMechanism_Advanced()
{
}


void SearchMechanism_Advanced::search(std::string stringToFind)
{

}


FoundStringsData & SearchMechanism_Advanced::getFoundData()
{
	return foundStringsBuff;
}





SearchMechanism_Factory::SearchMechanism_Factory()
{
	GetSystemInfo(&sysInfo);
}


SearchMechanism_Factory::~SearchMechanism_Factory()
{
}


SearchMechanism * SearchMechanism_Factory::getSearchMechanism(FilesData &fileToRead)
{
	typedef unsigned __int64 fsize_t;
 	fsize_t granularity = static_cast<fsize_t> (sysInfo.dwAllocationGranularity);
	fsize_t file = fileToRead.getSize();

	if (file < granularity * 100)
		return new SearchMechanism_Simple(fileToRead);
	else
		return new SearchMechanism_Advanced(fileToRead);
}

