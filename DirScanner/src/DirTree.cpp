#include "DirTree.h"

DirTree::DirTree(std::string dir)
	:
	_dir(dir)
{
}

DirTree::~DirTree()
{
}

std::string DirTree::preOrderTraverse()
{
	return _dir + "\\" + (*it).preOrderTraverse();
}

std::string DirTree::getDir()
{
	return _dir;
}

int DirTree::addElement(std::string dir)
{
	_tree.insert(DirTree(dir));
	return 1;
}

bool DirTree::operator==(const std::string str) const
{
	return _dir == str;
}

bool DirTree::operator<(const DirTree & tree) const
{
		if (_dir < tree._dir)
			return true;
		else
			return false;
}


//_dir + '\\' + ++it->getDir();