#pragma once

#include "opencv2/core/core.hpp"
#include "PhotographicRequirements.h"

class RequirementOutput
{
public:
	std::string outputName;
	Requirement *requirement;

public:
	RequirementOutput(std::string outputName, Requirement* &requirement)
	{
		this->outputName = outputName;
		this->requirement = requirement;
	}
};

class NetworkOutputs
{
public:
	std::vector<RequirementOutput *> vectorOutputs;

public:
	NetworkOutputs(){}

	~NetworkOutputs()
	{
		std::vector<RequirementOutput *>().swap(this->vectorOutputs);
	}

	void addOutput(RequirementOutput *output)
	{
		this->vectorOutputs.push_back(output);
	}

	std::vector<std::string> getOutputNames()
	{
		std::vector<std::string> outputNames;
		for (RequirementOutput *output : this->vectorOutputs)
			outputNames.push_back(output->outputName);
		return outputNames;
	}

	void parse(std::vector<std::vector<cv::Mat>> graphOutputs)
	{
		assert(graphOutputs.size() == this->vectorOutputs.size());

		std::size_t nOutputs = this->vectorOutputs.size();
		for (size_t i = 0; i < nOutputs; i++)
		{
			RequirementOutput *currentOutput = this->vectorOutputs[i];
			parseSigmoidOutput(graphOutputs[i][0], currentOutput->requirement->value, currentOutput->requirement->complianceDegree);
		}
	}

private:
	static void parseSigmoidOutput(cv::Mat output, REQUIREMENT_VALUE& value, int& complianceDegree)
	{
		cv::Point maxLoc;
		cv::minMaxLoc(output, NULL, NULL, (cv::Point *)0, &maxLoc);

		complianceDegree = (int)(output.at<float>(0, 0) * 100.0f);
		value = (complianceDegree >= 50) ? REQUIREMENT_VALUE::COMPLIANT : REQUIREMENT_VALUE::NON_COMPLIANT;
	}

};

