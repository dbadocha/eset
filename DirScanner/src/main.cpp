#include "DirScanner.h"

#include <iostream>
#include <windows.h>


int main()
{
	std::string path = "C:\\*";

	ScannerUtility utility;
	utility.findFirstFile(path.c_str());

	if (!utility.isValid())
		return 1;
	do
	{
		std::cout << utility.getFileName() << '\n';
	} while (utility.findNextFile() != 0);

	return 0;
}