#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>
#include <mutex>
#include "FilesData.h"
#include "FoundFilesGenerator.h"
#include "FileMaping.h"
#include "FileScanner.h"

#include <ctime>

void readStream(std::ifstream &stream, int pos, std::mutex &mtx)
{
	//std::this_thread::sleep_for(std::chrono::milliseconds(10));
	char * buffer = new char[21];
	mtx.lock();
	stream.seekg(pos);
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	stream.read(buffer, 20);
	mtx.unlock();
	std::cout << std::string(buffer, 20) << "\n";
}

void readStream2(std::string path, int pos)
{
	char * buffer = new char[51];
	std::ifstream fileInput;
	fileInput.open(path.c_str(), std::ifstream::in | std::ifstream::binary);
	fileInput.seekg(pos);
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	fileInput.read(buffer, 50);
	std::cout << std::string(buffer, 20) << "\n";
	fileInput.close();
}

class iTest
{
public:
	virtual void print() = 0;
};

class Test1 : public iTest
{
public:
	void print();
};

void Test1::print()
{
	std::cout << "test1\n";
}

class Test2 : public iTest
{
public:
	void print();
};

void Test2::print()
{
	std::cout << "test2\n";
}

class Watek
{
private:
	std::shared_ptr<iTest> &_test;
public:
	Watek(std::shared_ptr<iTest> &test);
	void print();
	void operator()();
};

Watek::Watek(std::shared_ptr<iTest> &test) : _test(test){}
void Watek::print() { _test.get()->print(); }
void Watek::operator()() {
	print();
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	print();
}

int main() {
	srand(time(NULL));
	////std::string path = "C:/adb/TableTextServiceArray.txt";
	//std::string path = "C:/adb/dousuniecia2.txt";
	////std::string pattern = "\n";
	//std::string pattern = "ullamcorper";
	////std::string path = "C:/adb/dousuniecia.txt";
	////std::string pattern = "\"test data sasdasdasdasdghdfgh\" ";
	clock_t start;

	//printf("100% moje \n");
	//start = clock();
	//FoundFilesGenerator filesGen1(path);
	//FilesContainer filesContainer1;
	//filesContainer1.push(filesGen1.next());

	//IFileReader_Generator *reader = new FileReader_ifstream(*filesContainer1.front());
	//FileScanner fs(*reader);

	//fs.scanFile(pattern);

	//printf("Czas wykonywania: %lu ms\n", clock() - start);


	start = clock();
	std::mutex mtx;

	auto test1 = std::shared_ptr<iTest>(new Test2());

	std::thread thd1(Watek(std::ref(test1)));

	test1.reset(new Test1());

	thd1.join();

	printf("Czas wykonywania: %lu ms\n", clock() - start);


	_getch();
}