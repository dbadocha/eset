#include "SearchManager.h"


SearchRequestsContainer::SearchRequestsContainer()
	: searchFactory()
{
}


SearchRequestsContainer::~SearchRequestsContainer()
{
}


void SearchRequestsContainer::addSearchRequest(FileData &fileToSearch)
{
	SearchMechanism * tmp = searchFactory.getSearchMechanism(fileToSearch);
	this->push_back(tmp);
}


SearchMechanism * SearchRequestsContainer::getSearchRequest()
{
	return this->back();
}




SearchManager::SearchManager(FilesListContainer &fQueue)
	: queueHandler(fQueue), reqContainer(), foundStrings()
{
}


SearchManager::~SearchManager()
{
}


void SearchManager::createReq()
{
	FileData &data = queueHandler.front();
	reqContainer.addSearchRequest(data);
	queueHandler.pop();
}


void SearchManager::startReq()
{
	reqContainer.getSearchRequest()->search("test");
}


void SearchManager::searchNext()
{
	createReq();
	startReq();
}