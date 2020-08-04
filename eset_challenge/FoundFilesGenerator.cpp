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





FoundFilesGenerator_Base::FoundFilesGenerator_Base(std::string path)
{
	pathList.push_back(Path::normalizePath(path));
}


FoundFilesGenerator_Base::~FoundFilesGenerator_Base()
{
	FindClose(hFind);
}


bool FoundFilesGenerator_Base::isFile()
{
	if (!(winFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && isValid())
		return true;
	else
		return false;
}


bool FoundFilesGenerator_Base::isDir()
{
	if (winFindData.dwFileAttributes & (FILE_ATTRIBUTE_DIRECTORY)
		&& !(winFindData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)
		&& isValid()
		&& winFindData.cFileName[0] != '.')
		return true;
	else
		return false;
}


bool FoundFilesGenerator_Base::isValid()
{
	if (hFind != INVALID_HANDLE_VALUE)
		return true;
	else
		return false;
}


std::string FoundFilesGenerator_Base::getPath()
{
	return pathMem;
}


fileSize_t FoundFilesGenerator_Base::getSize()
{
	if (!isFile())
		return 0;

	fileSize_t tmpSize = static_cast<unsigned long long>(winFindData.nFileSizeHigh) << bitOffset;
	tmpSize = tmpSize | winFindData.nFileSizeLow;
	return tmpSize;
}






FoundFilesGenerator_Dir::FoundFilesGenerator_Dir(std::string path, std::string extention)
	:
	FoundFilesGenerator_Base(path),
	extention(extention)
{
	std::transform(extention.begin(), extention.end(), extention.begin(), ::tolower);
	pathList.push_back(Path::normalizePath(path));
}


FoundFilesGenerator_Dir::~FoundFilesGenerator_Dir()
{
}


FileData *FoundFilesGenerator_Dir::next()
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

		if (isDir())
		{
			pathList.push_back(Path::moveUp(getPath(), winFindData.cFileName));
		}
		else if (isFile() && checkExt())
		{
			return new FileData(winFindData.cFileName, getPath(), getSize());
		}
	}
	return NULL;
}


bool FoundFilesGenerator_Dir::checkExt()
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





FoundFilesGenerator_File::FoundFilesGenerator_File(std::string path)
	: FoundFilesGenerator_Base(path)
{
}


FoundFilesGenerator_File::~FoundFilesGenerator_File()
{
}


FileData *FoundFilesGenerator_File::next()
{
	if (pathList.empty() || !Path::isFile(pathList.front()))
	{
		return NULL;
	}
	pathMem = pathList.front();
	hFind = FindFirstFileA(pathMem.c_str(), &winFindData);
	pathList.pop_front();

	return new FileData(winFindData.cFileName, Path::moveDown(pathMem), getSize());
}





FoundFilesGenerator::FoundFilesGenerator(std::string path, std::string range)
{
	if (Path::isFile(path))
		generator = new FoundFilesGenerator_File(path);
	else
		generator = new FoundFilesGenerator_Dir(path, range);
}


FoundFilesGenerator::~FoundFilesGenerator()
{
}


FileData *FoundFilesGenerator::next()
{
	return generator->next();
}