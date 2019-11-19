#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>
#include "FilesData.h"
#include "FoundFilesGenerator.h"
#include "FileMaping.h"
#include "SearchRequestManager.h"
#include "Test.h"


int main() {

	//FilesListProducer dir(fQueue);

	//// GetLastError  if (hFile == ERROR_FILE_NOT_FOUND)

	//Test_FileReader test_rf;
	//Test_SearchPage test_sp;

	//FoundFilesGenerator *test = new FoundFilesGeneratorDir("C://adb", "txt");
	FoundFilesGenerator *test = new FoundFilesGenerator_File("C://adb//adb.exe");

	FilesData * pointer = NULL;
	int i = 0;

	while (pointer != NULL || i == 0)
	{
		pointer = test->findNext();


		if (pointer != NULL)
			std::cout << i << ": " << pointer->getFilePath() << std::endl;
		++i;

		delete pointer;
	}
	delete test;

	_getch();
}