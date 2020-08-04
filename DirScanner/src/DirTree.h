#pragma once

#include <set>
#include <string>
#include <memory>

class DirTree
{
public:
	int addElement(std::string path);

private:
	std::string _dir;
	std::set<std::unique_ptr<DirTree>> _tree;
};


//check if it's in the set
//