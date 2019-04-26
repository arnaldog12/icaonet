#include <iostream>
#include "FvcHeader.h"
#include "OutputFile.h"
#include "FileUtils.h"
#include "opencv2/highgui/highgui.hpp"

bool checkImageFormat(std::string fileName);

int main(int argc, char *argv[]) 
{
	int retVal = SUCCESS;
	if (argc != 3) retVal = NO_MORE_INFO;

	std::string faceImageFile(argv[1]);
	std::string outputFile(argv[2]);
	OutputFile *outFile = new OutputFile(outputFile);

	if (!checkImageFormat(faceImageFile)) retVal = UNSUPPORTED_IMAGE_FORMAT;

	cv::Mat im = cv::imread(faceImageFile, cv::IMREAD_ANYCOLOR);
	if (im.empty()) retVal = UNUSEFUL_IMAGE_CONTENT;

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

bool checkImageFormat(std::string fileName)
{
	std::string ext = FileUtils::getFileExtension(fileName);
	std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
	return ext.compare("png") == 0 || ext.compare("jpg") == 0 || ext.compare("bmp") == 0;
}