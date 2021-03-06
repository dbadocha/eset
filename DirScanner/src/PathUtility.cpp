#include "PathUtility.h"

#include <algorithm>


WIN32_FIND_DATAA PathUtility::_winFindData = {};
HANDLE PathUtility::_hFind = {};

std::string PathUtility::normalizePath(std::string path)
{
	if (!path.length())
		return std::string();

	if (path.length() > MAX_PATH)
		return std::string();

	trimPath(path);
	separatorUnification(path);
	eraseEndSeparator(path);

	return path;
}

std::string PathUtility::changeDirDown(std::string dir)
{
	std::string tmp = normalizePath(dir);
	int pos = tmp.find_last_of('\\');
	if (pos == tmp.length()) {
		return NULL;
	}
	return tmp.substr(0, pos);
}

std::string PathUtility::concatDir(std::string path, std::string file)
{
	if (hasFileExtension(path))
		changeDirDown(path);

	if (!file.length())
		return normalizePath(path);

	return normalizePath(path) + '\\' + normalizePath(file);
}

std::string PathUtility::getFileName(std::string path)
{
	std::string tmp = normalizePath(path);

	if (!hasFileExtension(path))
		return std::string();

	int pos = path.find_last_of('\\');

	return tmp.substr(pos + 1);
}

int PathUtility::trimPath(std::string & path)
{
	path.erase(path.find_last_not_of(" \n\r\t") + 1);
	return 0;
}

int PathUtility::separatorUnification(std::string & path)
{
	std::replace(path.begin(), path.end(), '/', '\\');
	return 0;
}

int PathUtility::eraseEndSeparator(std::string & path)
{
	if (path.find_last_of('\\') == (path.length() - 1))
		path.erase(path.length() - 1);

	return 0;
}

bool PathUtility::hasFileExtension(std::string path)
{
	int dotPosFromEnd = path.length() - path.find_last_of('.');
	if (dotPosFromEnd == 0 || dotPosFromEnd > 5)
		return false;
	return true;
}
