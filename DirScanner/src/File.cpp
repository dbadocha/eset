#include "File.h"
#include "PathUtility.h"

#include <cassert>

File::File(std::string path, size_t size)
	:
	_name(PathUtility::getFileName(path)),
	_path(path),
	_size(size)
{
}


File::File(std::string name, std::string dir, size_t size)
	:
	_name(name),
	_path(PathUtility::normalizePath(dir) + "\\" + name),
	_size(size)
{
}


File::~File()
{
}


std::string File::getName()
{
	return _name;
}


std::string File::getDir()
{
	return PathUtility::changeDirDown(_path);
}


std::string File::getPath()
{
	return _path;
}


size_t File::getSize()
{
	return _size;
}