#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::experimental::filesystem;

int main()
{
	std::string exeFile = "..\\FVCSubmission\\x64\\Release\\Check.exe";
	std::string outFile = "out.txt";

	std::string folderPath = "C:\\Users\\Arnaldo\\Documents\\GitHub\\doutorado\\data\\val\\FVC\\images\\";
	for (const auto &file : fs::directory_iterator(folderPath))
	{
		char command[256];
		sprintf_s(command, "%s %s %s", exeFile.c_str(), file.path().string().c_str() , outFile.c_str());
		std::cout << command << std::endl << std::endl;
		std::system(command);
	}

	return 0;
}