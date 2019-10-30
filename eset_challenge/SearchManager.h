#pragma once
#include <string>
#include <list>
#include "FilesListContainer.h"
#include "SearchMechanism.h"
#include "FoundStringContainer.h"

class SearchRequestsContainer : protected std::list<SearchMechanism *>
{
private:
	SearchMechanism_Factory searchFactory;

public:
	SearchRequestsContainer();
	~SearchRequestsContainer();

	void addSearchRequest(FileData &fileToSearch);
	SearchMechanism * getSearchRequest();
	void concatFoundStringLists(FoundStringContainer &mainContainer);
};



class SearchManager
{
private:
	SearchRequestsContainer reqContainer;
	FoundStringContainer foundStrings;
	FilesListContainer &queueHandler;

	void createReq();
	void startReq();

public:
	SearchManager(FilesListContainer &fQueue);
	~SearchManager();

	void searchNext();
	void searchAll();
};



