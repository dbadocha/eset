#include "FoundFilesGenerator.h"

std::string Path::normalizePath(std::string path)
{
	if (!path.length())
		return path;

	if (path.length() > MAX_PATH)
		return "";

	std::string tmp = path;
	tmp.erase(tmp.find_last_not_of(" \n\r\t") + 1);
	std::replace(tmp.begin(), tmp.end(), '/', '\\');

	if (tmp.find_last_of('\\') == (tmp.length() - 1))
		tmp.erase(tmp.length() - 1);

	return tmp;
}


std::string Path::moveDown(std::string path)
{
	std::string tmp = normalizePath(path);
	int pos = tmp.find_last_of('\\');
	if (pos == tmp.length()) {
		return NULL;
	}
	return tmp.substr(0, pos);
}


std::string Path::moveUp(std::string path, std::string dir)
{
	return normalizePath(path) + '\\' + normalizePath(dir);
}


bool Path::isFile(std::string path)
{
	WIN32_FIND_DATAA winFindData;
	HANDLE hFind;

	hFind = FindFirstFileA(normalizePath(path).c_str(), &winFindData);

	if (!(winFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && hFind != INVALID_HANDLE_VALUE)
		return true;
	else
		return false;
}





FoundFilesGenerator::FoundFilesGenerator(std::string path, std::string extention)
	: extention(extention)
{
	std::transform(extention.begin(), extention.end(), extention.begin(), ::tolower);
	pathList.push_back(Path::normalizePath(path));
}


FoundFilesGenerator::~FoundFilesGenerator()
{
}


bool FoundFilesGenerator::_isFile()
{
	if (!(winFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && _isValid())
		return true;
	else
		return false;
}


bool FoundFilesGenerator::_isDir()
{
	if (winFindData.dwFileAttributes & (FILE_ATTRIBUTE_DIRECTORY)
		&& !(winFindData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)
		&& _isValid()
		&& winFindData.cFileName[0] != '.')
		return true;
	else
		return false;
}


bool FoundFilesGenerator::_checkExt()
{
	if (extention == "*")
		return true;

	std::string fileName = winFindData.cFileName;
	int pos = fileName.find_last_of('.');

	fileName = fileName.substr(pos + 1);
	std::transform(fileName.begin(), fileName.end(), fileName.begin(), ::tolower);

	if (fileName == extention)
		return true;

	return false;
}


bool FoundFilesGenerator::_isValid()
{
	if (hFind != INVALID_HANDLE_VALUE)
		return true;
	else
		return false;
}

std::string FoundFilesGenerator::getPath()
{
	return pathMem;
}


fileSize_t FoundFilesGenerator::getSize()
{
	if (!_isFile())
		return 0;

	fileSize_t tmpSize = static_cast<unsigned long long>(winFindData.nFileSizeHigh) << bitOffset;
	tmpSize = tmpSize | winFindData.nFileSizeLow;
	return tmpSize;
}

FilesData *FoundFilesGenerator::findNext()
{
	while (!pathList.empty() || hFind != 0)
	{
		if (hFind == 0 && !pathList.empty())
		{
			hFind = FindFirstFileA(Path::moveUp(pathList.front(), "*").c_str(), &winFindData);
			pathMem = pathList.front();
			pathList.pop_front();
		}
		else
		{
			if (FindNextFileA(hFind, &winFindData) == 0)
			{
				FindClose(hFind);
				hFind = 0;
				continue;
			}
		}

		if (_isDir())
		{
			pathList.push_back(Path::moveUp(getPath(), winFindData.cFileName));
		}
		else if (_isFile() && _checkExt())
		{
			return new FilesData(winFindData.cFileName, getPath(), getSize());
		}
	}
	return NULL;
}