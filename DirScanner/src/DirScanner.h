#pragma once

#include "File.h"

#include <vector>
#include <string>
#include <windows.h>

namespace DirScanner
{
	class DirScanner
	{
	public:
		DirScanner();
		~DirScanner();
		std::vector<File> scan(std::string path);
		std::vector<File> scan(std::string dir, std::string fileExt);
		std::vector<File> scanDir(std::string &path);
	};


	class ScanningMechanism
	{
	public:
		ScanningMechanism(std::string path);
		~ScanningMechanism();
	private:
		std::string _path;
		std::vector<File> fileScan();
		std::vector<File> dirScan();
		std::vector<File> recursiveDirScan();

	};

	class ScannerUtility
	{
	public:
		ScannerUtility();
		~ScannerUtility();
		bool FindFirstFile(LPCSTR lpFileName);
		bool FindNextFile();
		bool isFile();
		bool isDir();
		bool isValid();
		size_t getSize();
	private:
		WIN32_FIND_DATAA _winFindData;
		HANDLE _hFind;
	};
}