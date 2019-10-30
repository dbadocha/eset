#include "SearchDir.h"



SearchDir::SearchDir(FilesListContainer &queueHandler)
	: queueHandler(queueHandler)
{
}


SearchDir::~SearchDir()
{
}

//do zrobienie normalizacja wejœcia
void SearchDir::listDir(std::string dir)
{
	inputPathNorm(dir);
	std::string tmp = dir + "*";

	if (pathCheck(tmp))
		return;
		//exit(1);

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	ULONGLONG tmpSize = 0;

	hFind = FindFirstFile(tmp.c_str(), &FindFileData);

	do
	{
		if (FindFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
			std::basic_string<TCHAR> fileName = FindFileData.cFileName;

			if (fileName != "." && fileName != "..") {
				tmp = dir + "\\" + FindFileData.cFileName;
				this->listDir(tmp.c_str());
			}
		}
		else
		{
			tmpSize = static_cast<unsigned long long>(FindFileData.nFileSizeHigh) << bitOffset;
			tmpSize = tmpSize | FindFileData.nFileSizeLow;
			queueHandler.push(FindFileData.cFileName, dir, tmpSize);
		}

	} while (FindNextFile(hFind, &FindFileData) != 0);
	
}

int SearchDir::pathCheck(std::string &path)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	hFind = FindFirstFile(path.c_str(), &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
		return 1;
	else
		return 0;
}

void SearchDir::inputPathNorm(std::string &path)
{
	int pos = path.size() - path.find_last_of(".");
	if (pos < 6) {
		while (path.back() == ' ') {
			path.pop_back();
		}
	}
	else
		if (path.back() != '\\')
			path.push_back('\\');
}