#include <iostream>
#include <conio.h>
#include "FilesQueue.h"
#include "SearchDir.h"
#include "FileMaping.h"

#include <fstream>
#include <memoryapi.h>

int main() {
	FilesQueue kolejka;

	//SearchDir dir(kolejka);
	//dir.listDir("C:\\adb");
	////dir.listDir("C:\\Games\\Max Payne 3");
	//kolejka.print();
	//std::string path = "C:\\adb\\dousuniecia.txt";

	//SIZE_T size = GetLargePageMinimum();
	//// SEC_LARGE_PAGES

	////ERROR_INVALID_HANDLE  ERROR_ALREADY_EXISTS

	//// GetLastError  if (hFile == ERROR_FILE_NOT_FOUND)


	FileMaping wewe("C:\\adb\\dousuniecia2.txt");

	_getch();
}