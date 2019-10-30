#pragma once
#include <string>
#include <iostream>

class Compare
{
	typedef std::string srt_t;
	int offset;

public:
	Compare();
	~Compare();

	int compare_str_char(srt_t *fileString, char toFindString[128], int char_len);
};