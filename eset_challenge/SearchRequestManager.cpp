#include "SearchRequestManager.h"


SearchRequestsContainer::SearchRequestsContainer()
	: searchFactory()
{
}


SearchRequestsContainer::~SearchRequestsContainer()
{
}


void SearchRequestsContainer::addSearchRequest(FilesData &fileToSearch)
{
	SearchMechanism * tmp = searchFactory.getSearchMechanism(fileToSearch);
	this->push_back(tmp);
}


SearchMechanism * SearchRequestsContainer::getSearchRequest()
{
	return this->back();
}




SearchRequestManager::SearchRequestManager(FilesContainer &fQueue)
	: queueHandler(fQueue), reqContainer(), foundStrings()
{
}


SearchRequestManager::~SearchRequestManager()
{
}


void SearchRequestManager::createReq()
{
	FilesData tmp = *queueHandler.front();
	FilesData &data = tmp;
	reqContainer.addSearchRequest(data);
	queueHandler.pop();
}


void SearchRequestManager::startReq(std::string &toFind)
{
	reqContainer.getSearchRequest()->search(toFind);
}


void SearchRequestManager::searchNext(std::string &toFind)
{
	if (queueHandler.empty())
		return;

	createReq();
	startReq(toFind);
}