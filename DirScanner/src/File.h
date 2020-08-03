#include <string>

class File
{
private:
	std::string _name;
	std::string	_path;
	size_t _size;

public:
	File(std::string path, size_t size);
	File(std::string name, std::string dir, size_t size);
	~File();

	std::string getName();
	std::string getDir();
	std::string getPath();
	size_t getSize();
};