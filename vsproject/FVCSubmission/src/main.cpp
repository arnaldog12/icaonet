#include <iostream>
#include "FvcHeader.h"
#include "OutputFile.h"
#include "FileUtils.h"
#include "ICAONet.h"
#include "opencv2/highgui/highgui.hpp"

using deeplearning::TensorflowGraph;

ErrorCode checkArgs(int argc);
ErrorCode checkImageFormat(std::string fileName);
ErrorCode checkImageContent(cv::Mat im);

int main(int argc, char *argv[]) 
{
	ErrorCode errorCode = ErrorCode::SUCCESS;
	errorCode = checkArgs(argc);

	std::string faceImageFile(argv[1]);
	std::string outputFile(argv[2]);
	OutputFile *outFile = new OutputFile(outputFile);

	errorCode = (errorCode == ErrorCode::SUCCESS) ? checkImageFormat(faceImageFile) : errorCode;

	cv::Mat im = cv::imread(faceImageFile, cv::IMREAD_ANYCOLOR);
	errorCode = (errorCode == ErrorCode::SUCCESS) ? checkImageContent(im) : errorCode;

	if (errorCode != ErrorCode::SUCCESS)
		outFile->write(faceImageFile, errorCodeToRetVal(errorCode));
	else
	{
		Eye *rightEye = new Eye();
		Eye *leftEye = new Eye();

		PhotographicRequirements *reqs = ICAONet::run(im, errorCode);

		outFile->write(faceImageFile, errorCodeToRetVal(errorCode), rightEye, leftEye, reqs);

		delete rightEye;
		delete leftEye;
		delete reqs;
	}
	
	outFile->close();
	delete outFile;
	return errorCode;
}

ErrorCode checkArgs(int argc)
{
	return (argc == 3) ? ErrorCode::SUCCESS : ErrorCode::SYNTAX_ERROR;
}

ErrorCode checkImageFormat(std::string fileName)
{
	std::string ext = FileUtils::getFileExtension(fileName);
	std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
	bool isOk = (ext.compare(".png") == 0 || ext.compare(".jpg") == 0 || ext.compare(".bmp") == 0);
	return isOk ? ErrorCode::SUCCESS : ErrorCode::CANNOT_OPEN_IMAGE_FILE;
}

ErrorCode checkImageContent(cv::Mat im)
{
	return !im.empty() ? ErrorCode::SUCCESS : ErrorCode::IMAGE_LOAD_ERROR;
}