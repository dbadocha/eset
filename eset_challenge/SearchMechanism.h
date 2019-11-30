#pragma once

#include <windows.h>
#include "FoundStringData.h"
#include "FilesData.h"
#include "FileReader.h"

class SearchMechanism_Data
{
protected:
	FilesData fileToRead;
	FoundStringDataContainer FoundStringDatasBuff;
	std::string *toFind = NULL;
	FileReader *fileReader;

public:
	SearchMechanism_Data(FilesData &fileToRead);
	~SearchMechanism_Data();
};


class SearchMechanism
{
public:
	SearchMechanism();
	~SearchMechanism();

	virtual void search(std::string stringToFind) = 0;
	virtual FoundStringDataContainer *getFoundData() = 0;
};


class SearchMechanism_Simple : public SearchMechanism_Data, public SearchMechanism
{
public:
	SearchMechanism_Simple(FilesData &fileToRead);
	~SearchMechanism_Simple();

	void search(std::string stringToFind);
	FoundStringDataContainer *getFoundData();
};


class SearchMechanism_Advanced : public SearchMechanism_Data, public SearchMechanism
{
public:
	SearchMechanism_Advanced(FilesData &fileToRead);
	~SearchMechanism_Advanced();

	void search(std::string stringToFind);
	FoundStringDataContainer *getFoundData();
};


class SearchMechanism_Factory
{
private:
	_SYSTEM_INFO  sysInfo;

public:
	SearchMechanism_Factory();
	~SearchMechanism_Factory();

	SearchMechanism *getSearchMechanism(FilesData &fileToSearch);
};