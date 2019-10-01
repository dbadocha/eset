#include "FilesQueue.h"

FilesQueue::FilesQueue() : std::queue<FileData>()
{
}


FilesQueue::~FilesQueue()
{
}

void FilesQueue::push(std::string fileName, std::string filePath, unsigned long long size)
{
	std::queue<FileData>::push(FileData(fileName, filePath, size));
}

void FilesQueue::print()
{
	while (!std::queue<FileData>::empty()) {
		std::cout << std::queue<FileData>::front().getFilePath() << "\n";
		std::queue<FileData>::pop();
	}
}