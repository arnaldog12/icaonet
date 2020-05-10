#include <iostream>
#include <filesystem>
#include <fstream>
#include <ctime>
#include <chrono>

namespace fs = std::experimental::filesystem;
using namespace std::chrono;

int main()
{
	std::string exeFile = "..\\FVCSubmission\\x64\\Release\\Check.exe";
	std::string outFile = "out.txt";

	std::string folderPath = "C:\\Users\\arnal\\Documents\\GitHub\\doutorado\\data\\pybossa\\images\\";

	high_resolution_clock::time_point start = high_resolution_clock::now();
	for (const auto &file : fs::directory_iterator(folderPath))
	{
		char command[256];
		sprintf_s(command, "%s %s %s", exeFile.c_str(), file.path().string().c_str() , outFile.c_str());
		std::cout << command << std::endl << std::endl;
		std::system(command);
	}
	high_resolution_clock::time_point end = high_resolution_clock::now();
	
	duration<double> time_span = duration_cast<duration<double>>(end - start);
	std::cout << "Total Time " << time_span.count() << " seconds.";
	std::cout << std::endl;

	return 0;
}