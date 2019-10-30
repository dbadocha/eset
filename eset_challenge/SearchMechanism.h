#pragma once

#include <windows.h>
#include "FoundStringContainer.h"
#include "FilesListContainer.h"
#include <fstream>

class SearchMechanism_Data
{
protected:
	FileData fileToSearch;
	FoundStringContainer foundStringsBuff;
	std::string stringToFind;

public:
	SearchMechanism_Data(FileData &fileToSearch);
	~SearchMechanism_Data();
};


class SearchMechanism
{
public:
	SearchMechanism();
	~SearchMechanism();

	virtual void setStringToFind(std::string &stringToFind) = 0;
	virtual void search(std::string stringToFind) = 0;
	virtual FoundStringContainer &getFoundData() = 0;
};


class SearchMechanism_Simple : public SearchMechanism_Data, public SearchMechanism
{
public:
	SearchMechanism_Simple(FileData &fileToSearch);
	~SearchMechanism_Simple();

	void setStringToFind(std::string &stringToFind);
	void search(std::string stringToFind);
	FoundStringContainer &getFoundData();
};


class SearchMechanism_Advanced : public SearchMechanism_Data, public SearchMechanism
{
public:
	SearchMechanism_Advanced(FileData &fileToSearch);
	~SearchMechanism_Advanced();

	void setStringToFind(std::string &stringToFind);
	void search(std::string stringToFind);
	FoundStringContainer &getFoundData();
};


class SearchMechanism_Factory
{
private:
	_SYSTEM_INFO  sysInfo;

public:
	SearchMechanism_Factory();
	~SearchMechanism_Factory();

	SearchMechanism * getSearchMechanism(FileData &fileToSearch);
};