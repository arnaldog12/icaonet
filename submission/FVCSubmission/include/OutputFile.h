#pragma once
#include <iostream>
#include <fstream>
#include "Eye.h"
#include "FileUtils.h"
#include "PhotographicRequirements.h"

class OutputFile
{
public:
	std::ofstream outputFile;
	
	OutputFile(std::string filePath)
	{
		this->outputFile = std::ofstream(filePath, std::ofstream::out || std::ofstream::app);
	}

	void write(std::string imageName, int retVal, Eye *rightEye = nullptr, Eye *leftEye = nullptr, PhotographicRequirements *reqs = nullptr)
	{
		outputFile << cv::format("%s %d", FileUtils::getFileName(imageName), retVal);
		if (retVal != SUCCESS)
		{
			outputFile << std::endl;
			return;
		}

		cv::Point leftEyeCenter = leftEye->center();
		cv::Point rightEyeCenter = rightEye->center();
		outputFile << cv::format(" %d %d %d %d ", leftEyeCenter.x, leftEyeCenter.y, rightEyeCenter.y, rightEyeCenter.x);
		for (Requirement *req : reqs->getRequirements())
			outputFile << cv::format("%d ", req->value);
		outputFile << std::endl;
	}

	void close()
	{
		this->outputFile.close();
	}
};