#include "DirScanner.h"
#include "PathUtility.h"

#include <iostream>
ScanningMechanism::ScanningMechanism()
{
}

ScanningMechanism::~ScanningMechanism()
{
	FindClose(_hFind);
}

bool ScanningMechanism::findFirstFile(LPCSTR lpFileName)
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

bool ScanningMechanism::findNextFile()
{
	return FindNextFileA(_hFind, &_winFindData);
}

bool ScanningMechanism::isFile()
{
	if (!(_winFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && isValid())
		return true;
	else
		return false;
}

bool ScanningMechanism::isDir()
{
	if (_winFindData.dwFileAttributes & (FILE_ATTRIBUTE_DIRECTORY)
		&& !(_winFindData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)
		&& isValid()
		&& _winFindData.cFileName[0] != '.')
		return true;
	else
		return false;
}

bool ScanningMechanism::isValid()
{
	if (_hFind != INVALID_HANDLE_VALUE)
		return true;
	else
		return false;
}

size_t ScanningMechanism::getSize()
{
	if (!isFile())
		return 0;

	size_t tmpSize = static_cast<size_t>(_winFindData.nFileSizeHigh) << bitOffset;
	tmpSize = tmpSize | _winFindData.nFileSizeLow;
	return tmpSize;
}

std::string ScanningMechanism::getFileName()
{
	return std::string(_winFindData.cFileName);
}

DirScanner::DirScanner()
{
}

DirScanner::~DirScanner()
{
}

std::vector<File> DirScanner::scan(std::string path)
{
	std::vector<File> ret;

	_scanner.findFirstFile(path.c_str());

	if (!_scanner.isValid())
		return std::vector<File>();

	do
	{

	} while (_scanner.findNextFile() != 0);

	return std::vector<File>();
}

std::vector<File> DirScanner::scan(std::string dir, ScannerFilter &filter)
{
	std::vector<File> ret;

	_scanner.findFirstFile(dir.c_str());

	if (!_scanner.isValid())
		return std::vector<File>();

	do
	{
		filter.check(_scanner);
	} while (_scanner.findNextFile() != 0);

	return std::vector<File>();
}

ScannerFilter_File::ScannerFilter_File(std::string extension)
	:
	_extension(extension)
{
}

bool ScannerFilter_File::check(ScanningMechanism &scanner)
{
	if (!scanner.isFile())
		return false;

	std::string name = scanner.getFileName();
	std::string ext = name.substr(name.length() - _extension.length());

	return (ext == _extension);
}

bool ScannerFilter_Dir::check(ScanningMechanism & scanner)
{
	if (scanner.isDir())
		return true;
	else
		return false;
}