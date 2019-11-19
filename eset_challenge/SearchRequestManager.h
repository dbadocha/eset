#pragma once
#include <string>
#include <list>
#include "FilesData.h"
#include "SearchMechanism.h"
#include "FoundStringsData.h"

class SearchRequestsContainer : protected std::list<SearchMechanism *>
{
private:
	SearchMechanism_Factory searchFactory;

public:
	SearchRequestsContainer();
	~SearchRequestsContainer();

	void addSearchRequest(FilesData &fileToSearch);
	SearchMechanism * getSearchRequest();
};



class SearchRequestManager
{
private:
	SearchRequestsContainer reqContainer;
	FoundStringsData foundStrings;
	FilesContainer &queueHandler;

	void createReq();
	void startReq(std::string &toFind);

public:
	SearchRequestManager(FilesContainer &fQueue);
	~SearchRequestManager();

	void searchNext(std::string &toFind);
	void searchAll();
};