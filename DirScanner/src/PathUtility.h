#pragma once
#include <string>

class PathUtility
{
public:
	static std::string normalizePath(std::string path);
	static std::string changeDirDown(std::string dir);
	static std::string concatDir(std::string dir, std::string file);
	static std::string getFileName(std::string path);
	static bool isFile(std::string path);
private:
	static int trimPath(std::string &path);
	static int separatorUnification(std::string &path);
	static int eraseEndSeparator(std::string &path);
	static bool hasFileExtension(std::string path);
};