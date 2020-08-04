#include "DirScanner.h"

#include <iostream>
#include <windows.h>


int main()
{
	std::string path = "C:\\Qt\\*";

	DirScanner scanner;

	ScannerFilter *dirFilter = new ScannerFilter_Dir();
	ScannerFilter *fileFilter = new ScannerFilter_File("txt");

	scanner.scan(path, *fileFilter);

	delete dirFilter;
	delete fileFilter;

	return 0;
}