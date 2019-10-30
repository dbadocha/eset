#include "Compare.h"



Compare::Compare()
{
}


Compare::~Compare()
{
}

int Compare::compare_str_char(srt_t *fileString, char toFindString[128], int char_len)
{
	int offset = 0, i = 0;
	while (offset < fileString->length())
	{
		if ((*fileString)[offset] == toFindString[i]) {
			std::cout << i << " " << (*fileString)[i] << std::endl;
			++i;
		}
		else
			i = 0;
	}

	if (i == 0)
		return std::string::npos;
	else
		return offset;
}