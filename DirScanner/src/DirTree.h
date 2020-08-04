#pragma once

#include <set>
#include <string>
#include <memory>


class DirTree
{
public:
	DirTree(std::string dir);
	~DirTree();
	std::string getDir();
	int addElement(std::string path);
	bool operator==(const std::string str) const;
	bool operator<(const DirTree &tree) const;

private:
	std::string _dir;
	std::set<DirTree>::iterator it;
	std::set<DirTree> _tree;
};


//check if it's in the set
//