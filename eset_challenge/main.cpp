#include <iostream>
#include <conio.h>
#include "FilesListContainer.h"
#include "SearchDir.h"
#include "FileMaping.h"
#include "SearchManager.h"


int main() {
	FilesListContainer fQueue;

	SearchDir dir(fQueue);
	dir.listDir("C:\\adb");

	//dir.listDir("C:\\Games\\Max Payne 3");
	//fQueue.print();
	//std::string path = "C:\\adb\\dousuniecia.txt";

	SIZE_T size = GetLargePageMinimum();
	// SEC_LARGE_PAGES

	//ERROR_INVALID_HANDLE  ERROR_ALREADY_EXISTS

	// GetLastError  if (hFile == ERROR_FILE_NOT_FOUND)


	//FileMaping wewe("C:\\adb\\dousuniecia2.txt");

	FilesListContainer test;
	test.push("test.txt", "C:\\adb", 166);
	fQueue.pop();
	fQueue.pop();
	

	SearchManager manager = SearchManager(test);
	manager.searchNext();

	_getch();
}