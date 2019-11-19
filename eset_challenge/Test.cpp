#include "Test.h"



Test::Test()
{
}


Test::~Test()
{
}


Test_FileReader::Test_FileReader()
{
	test_open();
	test_fetch();
}


Test_FileReader::~Test_FileReader()
{
}

int Test_FileReader::test_open_generic(FilesData &data)
{
	FileReader * rf = NULL;
	try
	{
		rf = new FileReader_Simple(data);
	}
	catch (std::runtime_error& e)
	{
		std::cout << "error: " << e.what() << std::endl;
		return -1;
	}
	delete rf;
	std::cout << "OK" << std::endl;
	return 0;
}

int Test_FileReader::test_open_OK()
{
	std::cout << "test_open_OK: \t";
	FilesData data("test.txt", "C:\\adb", 166);
	return test_open_generic(data);
}

int Test_FileReader::test_open_NOK()
{
	std::cout << "test_open_NOK: \t";
	FilesData data(".txt", "C:\\adb", 166);
	return test_open_generic(data);
}

void Test_FileReader::test_open()
{
	test_open_OK();
	test_open_NOK();
}



int Test_FileReader::test_fetch_OK()
{
	std::cout << "test_fetch_OK: \t";

	FilesData data("test.txt", "C:\\adb", 166);

	FileReader * rf = new FileReader_Simple(data);

	char buffer[4096];
	char * buff_2 = NULL;
	int len = 0;
	//len = rf->fetchData(buffer);
	buff_2 = new char[len+1];
	strncpy_s(buff_2, len+1, buffer, len);

	std::cout << buff_2 << std::endl;

	delete [] buff_2;
	return 0;
}

int Test_FileReader::test_fetch_NOK()
{
	return 0;
}

void Test_FileReader::test_fetch()
{
	test_fetch_OK();
	//test_fetch_NOK();
}




Test_SearchPage::Test_SearchPage()
{
	srand(static_cast<unsigned int> (time(NULL)));
	test_fillOffset();
}


Test_SearchPage::~Test_SearchPage()
{
}


int Test_SearchPage::test_fillOffset()
{
	std::cout << "test_fillOffset: \t";
	matchInfo *info;
	SearchPage * search;
	fileSize_t checkValue = 0;
	fileSize_t fileOffset = 0, pageOffset = 0;
	std::list <matchInfo> matchList;
	std::string srt = {};
	char * test = {};
	info = new matchInfo();
	search = new SearchPage(matchList, srt);

	for (int i = 0; i < 10000; ++i)
	{
		pageOffset = rand() * i;
		checkValue = fileOffset + pageOffset;

		info->pageOffset = pageOffset;
		fileOffset += pageOffset;
		search->nextPage(test, pageOffset);

		search->fillOffset(*info);
		
		if ((checkValue) != (std::stoll(info->stringData.offset)))
		{
			std::cout << "error: ";
			std::cout << checkValue << " != " << std::stol(info->stringData.offset) << std::endl;
			return -1;
		}
	}

	delete search;
	delete info;
	std::cout << "OK" << std::endl;
	return 0;
}


int Test_SearchPage::test_fillPrefix()
{
	std::list <matchInfo> matchList;

	std::string toFind = { "qwe" };
	std::string prefixMem = { "qwe" };
	
	SearchPage sp(matchList, toFind);

	for (int i = 0; i < 3; ++i)
	{
		sp.addNewMatch(i);
	}
	//sp.fillSuffix(matchInfo &toFill);
	return 0;
}


