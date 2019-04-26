#include <iostream>
#include "FvcHeader.h"
#include "OutputFile.h"
#include "FileUtils.h"
#include "opencv2/highgui/highgui.hpp"

int checkArgs(int argc);
int checkImageFormat(std::string fileName);
int checkImageContent(cv::Mat im);

int main(int argc, char *argv[]) 
{
	int retVal = SUCCESS;
	retVal = checkArgs(argc);

	std::string faceImageFile(argv[1]);
	std::string outputFile(argv[2]);
	OutputFile *outFile = new OutputFile(outputFile);

	retVal = checkImageFormat(faceImageFile);

	cv::Mat im = cv::imread(faceImageFile, cv::IMREAD_ANYCOLOR);
	retVal = checkImageContent(im);

	if (retVal != SUCCESS)
		outFile->write(faceImageFile, retVal);
	else
	{
		Eye *rightEye = new Eye();
		Eye *leftEye = new Eye();
		PhotographicRequirements *reqs = new PhotographicRequirements();

		delete rightEye;
		delete leftEye;
		delete reqs;
	}
	
	outFile->close();
	delete outFile;
	return retVal;
}

int checkArgs(int argc)
{
	return (argc == 3) ? SUCCESS : NO_MORE_INFO;
}

int checkImageFormat(std::string fileName)
{
	std::string ext = FileUtils::getFileExtension(fileName);
	std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
	bool isOk = (ext.compare("png") == 0 || ext.compare("jpg") == 0 || ext.compare("bmp") == 0);
	return isOk ? SUCCESS : UNSUPPORTED_IMAGE_FORMAT;
}

int checkImageContent(cv::Mat im)
{
	return !im.empty() ? SUCCESS : UNUSEFUL_IMAGE_CONTENT;
}