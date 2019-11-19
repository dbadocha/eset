#pragma once
#include <time.h>
#include <stdlib.h>

#include "FileReader.h"
#include "Compare.h"

class Test
{
private:
	//Test_FileReader test_rf;
	//Test_SearchPage test_sp;
public:
	Test();
	~Test();
};

class Test_FileReader
{
private:
	//int create_dummy_file();
	int test_open_generic(FilesData &data);
	int test_open_OK();
	int test_open_NOK();
	int test_fetch_OK();
	int test_fetch_NOK();

public:
	Test_FileReader();
	~Test_FileReader();

	void test_open();
	void test_fetch();
};

class Test_SearchPage
{
private:
	int test();
public:
	Test_SearchPage();
	~Test_SearchPage();

	int test_oneLine();
	int test_fillOffset();
	int test_fillPrefix();
};