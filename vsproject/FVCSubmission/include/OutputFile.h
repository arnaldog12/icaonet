#pragma once
#include <iostream>
#include <fstream>
#include "Eye.h"
#include "FileUtils.h"
#include "EvaluationResults.h"

class OutputFile
{
public:
	std::ofstream outputFile;
	
	OutputFile(std::string filePath)
	{
		this->outputFile.open(filePath, std::ofstream::app);
	}

	void write(std::string imageName, RetVal retVal, EvaluationResults* results = nullptr)
	{
		this->outputFile << cv::format("%s %d", FileUtils::getFileName(imageName).c_str(), retVal);
		if (retVal != RetVal::IMAGE_CAN_BE_PROCESSED)
		{
			this->outputFile << std::endl;
			return;
		}

		cv::Point leftEyeCenter = results->leftEye->center();
		cv::Point rightEyeCenter = results->rightEye->center();
		this->outputFile << cv::format(" %d %d %d %d", leftEyeCenter.x, leftEyeCenter.y, rightEyeCenter.x, rightEyeCenter.y);
		for (Requirement *req : results->photoReqs->getRequirements())
			this->outputFile << " " << reqToString(req);
		this->outputFile << std::endl;
	}

	void close()
	{
		this->outputFile.close();
	}

private:
	static std::string reqToString(Requirement *req)
	{
		switch (req->value)
		{
		case REQUIREMENT_VALUE::COMPLIANT:
		case REQUIREMENT_VALUE::NON_COMPLIANT:		return cv::format("%d", req->complianceDegree);
		case REQUIREMENT_VALUE::DUMMY:				return "?";
		case REQUIREMENT_VALUE::UNABLE_TO_EVALUATE: return "-";
		default: return "!";
		}
	}
};