#include "DirScanner.h"
#include "PathUtility.h"

DirScanner::DirScanner()
{
}

DirScanner::~DirScanner()
{
}

std::vector<File> DirScanner::scan(std::string path)
{
	std::vector<File> ret;

	if (!PathUtility::isValid(path))
		return ret;

	if (PathUtility::isFile(path))
		ret.push_back(File(path, 0));
	else
		scanDir(path);

	return std::vector<File>();
}

std::vector<File> DirScanner::scan(std::string dir, std::string fileExt)
{
	return std::vector<File>();
}

std::vector<File> DirScanner::scanDir(std::string & path)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	hFind = FindFirstFileEx(
		path.c_str(),
		FindExInfoBasic,
		&FindFileData,
		FindExSearchNameMatch,
		NULL,
		0);

	do
	{

	} while (FindNextFileA(hFind, &FindFileData) != 0);

	FindClose(hFind);

	return std::vector<File>();
}

ScanningMechanism::ScanningMechanism(std::string path)
{
}

ScanningMechanism::~ScanningMechanism()
{
}

std::vector<File> ScanningMechanism::fileScan()
{
	if (!PathUtility::isFile(_path))
		return std::vector<File>();

	_hFind = FindFirstFileEx(
		_path.c_str(),
		FindExInfoBasic,
		&_winFindData,
		FindExSearchNameMatch,
		NULL,
		0);

	if (_hFind == INVALID_HANDLE_VALUE)
		return std::vector<File>();
	FindClose(_hFind);

	return std::vector<File>();
}

ScannerUtility::ScannerUtility()
{
}

ScannerUtility::~ScannerUtility()
{
	FindClose(_hFind);
}

bool ScannerUtility::findFirstFile(LPCSTR lpFileName)
{
	_hFind = FindFirstFileEx(
		lpFileName,
		FindExInfoBasic,
		&_winFindData,
		FindExSearchNameMatch,
		NULL,
		0);

	return isValid();
}

bool ScannerUtility::findNextFile()
{
	return FindNextFileA(_hFind, &_winFindData);
}

bool ScannerUtility::isFile()
{
	if (!(_winFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && isValid())
		return true;
	else
		return false;
}

bool ScannerUtility::isDir()
{
	if (_winFindData.dwFileAttributes & (FILE_ATTRIBUTE_DIRECTORY)
		&& !(_winFindData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)
		&& isValid()
		&& _winFindData.cFileName[0] != '.')
		return true;
	else
		return false;
}

bool ScannerUtility::isValid()
{
	if (_hFind != INVALID_HANDLE_VALUE)
		return true;
	else
		return false;
}

size_t ScannerUtility::getSize()
{
	if (!isFile())
		return 0;

	size_t tmpSize = static_cast<size_t>(_winFindData.nFileSizeHigh) << bitOffset;
	tmpSize = tmpSize | _winFindData.nFileSizeLow;
	return tmpSize;
}
