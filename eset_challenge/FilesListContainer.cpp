#include "FilesListContainer.h"

FilesListContainer::FilesListContainer() : std::queue<FileData>()
{
}


FilesListContainer::~FilesListContainer()
{
}

void FilesListContainer::push(std::string fileName, std::string filePath, unsigned long long size)
{
	std::queue<FileData>::push(FileData(fileName, filePath, size));
}

void FilesListContainer::print()
{
	while (!std::queue<FileData>::empty()) {
		std::cout << std::queue<FileData>::front().getFilePath() << "\n";
		std::queue<FileData>::pop();
	}
}