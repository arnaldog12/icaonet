#pragma once

#include "opencv2/core/core.hpp"
#include "EvaluationResults.h"


class NetworkOutputs
{
public:
	static std::vector<std::string> getOutputNames()
	{
		std::vector<std::string> outputNames = {
			 //"output_reqs/Sigmoid:0",
			 "output_eyes/Sigmoid:0",
		};
		return outputNames;
	}

	static void parseRequirements(std::vector<std::vector<cv::Mat>> graphOutputs, PhotographicRequirements* &photoReqs)
	{
		std::vector<Requirement *> listReqs = photoReqs->getRequirements();
		size_t nReqs = listReqs.size();
		for (size_t i = 0; i < nReqs; i++)
			parseMultilabelOutput(graphOutputs[0][0], (int)i, listReqs[i]->value, listReqs[i]->complianceDegree);
	}

	static void parseEyes(std::vector<std::vector<cv::Mat>> graphOutputs, Eye* &rightEye, Eye* &leftEye, cv::Size imSize, cv::Point offset)
	{
		cv::Mat eyeOutput = graphOutputs[0][0];
		int width = imSize.width;
		int height = imSize.height;
		rightEye->leftCorner = cv::Point((int) (eyeOutput.at<float>(0, 0) * width), (int) (eyeOutput.at<float>(0, 1) * height)) + offset;
		rightEye->rightCorner = rightEye->leftCorner;
		leftEye->leftCorner = cv::Point((int) (eyeOutput.at<float>(0, 2) * width), (int) (eyeOutput.at<float>(0, 3) * height)) + offset;
		leftEye->rightCorner = leftEye->leftCorner;
	}

private:
	static void parseMultilabelOutput(cv::Mat output, int index, REQUIREMENT_VALUE& value, int& complianceDegree)
	{
		complianceDegree = (int)(output.at<float>(0, index) * 100.0f);
		value = (complianceDegree >= 50) ? REQUIREMENT_VALUE::COMPLIANT : REQUIREMENT_VALUE::NON_COMPLIANT;
	}
};
