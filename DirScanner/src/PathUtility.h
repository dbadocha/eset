#pragma once
#include <string>
#include <windows.h>

constexpr size_t bitOffset = sizeof(DWORD) * 8;

class PathUtility
{
public:
	static std::string normalizePath(std::string path);
	static std::string changeDirDown(std::string dir);
	static std::string concatDir(std::string dir, std::string file);
	static std::string getFileName(std::string path);
	static bool isFile(std::string &path);
	static bool isDir(std::string &path);
	static bool isValid(std::string &path);
	static size_t getSize(std::string &path);

private:
	static WIN32_FIND_DATAA _winFindData;
	static HANDLE _hFind;
	static int trimPath(std::string &path);
	static int separatorUnification(std::string &path);
	static int eraseEndSeparator(std::string &path);
	static bool hasFileExtension(std::string path);
};