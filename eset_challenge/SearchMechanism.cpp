#include "SearchMechanism.h"

SearchMechanism::SearchMechanism()
{
}

SearchMechanism::~SearchMechanism()
{
}





SearchMechanism_Data::SearchMechanism_Data(FileData &fileToSearch)
	: fileToSearch(fileToSearch)
{
}

SearchMechanism_Data::~SearchMechanism_Data()
{
}





SearchMechanism_Simple::SearchMechanism_Simple(FileData &fileToSearch)
	: SearchMechanism_Data(fileToSearch)
{
}


SearchMechanism_Simple::~SearchMechanism_Simple()
{
}


void SearchMechanism_Simple::setStringToFind(std::string &stringToFind)
{
	this->stringToFind = stringToFind;
}


void SearchMechanism_Simple::search(std::string stringToFind)
{
	std::string filePath = fileToSearch.getFilePath();
	std::ifstream fileInput;
	int offset = 0;
	std::string line;
	
	fileInput.open(filePath.c_str());

	if (!fileInput.is_open())
		throw std::runtime_error("Could not open file");

	while (!fileInput.eof())
	{
		getline(fileInput, line);
		while (offset != std::string::npos)
		{
			offset = line.find(stringToFind, offset);
			char tets[128] = "\"test data sasdasdasdasdghdfgh\"\"test" ;
			char * p = tets;
		}
	}

	fileInput.close();
}


FoundStringContainer & SearchMechanism_Simple::getFoundData()
{
	return foundStringsBuff;
}





SearchMechanism_Advanced::SearchMechanism_Advanced(FileData &fileToSearch)
	: SearchMechanism_Data(fileToSearch)
{

}


SearchMechanism_Advanced::~SearchMechanism_Advanced()
{
}


void SearchMechanism_Advanced::setStringToFind(std::string &stringToFind)
{
	this->stringToFind = stringToFind;
}


void SearchMechanism_Advanced::search(std::string stringToFind)
{

}


FoundStringContainer & SearchMechanism_Advanced::getFoundData()
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

SearchMechanism * SearchMechanism_Factory::getSearchMechanism(FileData &fileToSearch)
{
	typedef unsigned __int64 fsize_t;
 	fsize_t granularity = static_cast<fsize_t> (sysInfo.dwAllocationGranularity);
	fsize_t file = fileToSearch.getSize();

	if (file < granularity * 100)
		return new SearchMechanism_Simple(fileToSearch);
	else
		return new SearchMechanism_Advanced(fileToSearch);
}
