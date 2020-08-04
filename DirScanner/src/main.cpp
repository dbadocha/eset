#include <iostream>
#include <windows.h>

int main()
{
	std::string path = "C:\\adb\\*.*";
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	hFind = FindFirstFileEx(
		path.c_str(),
		FindExInfoBasic,
		&FindFileData,
		FindExSearchNameMatch,
		NULL,
		0);

	if (hFind == INVALID_HANDLE_VALUE)
		return 1;
	do
	{
		std::cout << FindFileData.cFileName << '\n';
	} while (FindNextFileA(hFind, &FindFileData) != 0);

	FindClose(hFind);

	return 0;
}