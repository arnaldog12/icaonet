#pragma once

#include "opencv2/core/core.hpp"
#include "PhotographicRequirements.h"
#include <math.h>

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
	std::vector<float> outputTemperatures;

public:
	NetworkOutputs()
	{
		this->outputTemperatures = {
			0.72023964f,
			1.6149887f,
			1.2930762f,
			1.217171f,
			0.9226482f,
			0.81680655f,
			0.77541435f,
			1.4967334f,
			1.7468733f,
			1.5217109f,
			1.1665096f,
			1.3844513f,
			1.8485f,
			1.0221235f,
			0.7438692f,
			1.1263908f,
			1.0265276f,
			0.16541567f,
			1.7934476f,
			1.6463976f,
			0.45624524f,
			1.2901064f,
			1.1938468f,
		};
	}

	~NetworkOutputs()
	{
		std::vector<RequirementOutput *>().swap(this->vectorOutputs);
		std::vector<float>().swap(this->outputTemperatures);
	}

	void addOutput(RequirementOutput *output)
	{
		this->vectorOutputs.push_back(output);
	}

	std::vector<std::string> getOutputNames()
	{
		std::vector<std::string> outputNames;
		//for (RequirementOutput *output : this->vectorOutputs)
		//	outputNames.push_back(output->outputName);
		outputNames.push_back("outputs/BiasAdd:0");
		return outputNames;
	}

	void parse(std::vector<std::vector<cv::Mat>> graphOutputs)
	{
		assert(graphOutputs.size() == this->vectorOutputs.size());

		std::size_t nOutputs = this->vectorOutputs.size();
		for (size_t i = 0; i < nOutputs; i++)
		{
			RequirementOutput *currentOutput = this->vectorOutputs[i];
			//parseSigmoidOutput(graphOutputs[i][0], currentOutput->requirement->value, currentOutput->requirement->complianceDegree);
			parseMultilabelOutput(graphOutputs[0][0], (int) i, currentOutput->requirement->value, currentOutput->requirement->complianceDegree, this->outputTemperatures[i]);
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

	static void parseMultilabelOutput(cv::Mat output, int index, REQUIREMENT_VALUE& value, int& complianceDegree, float temperature)
	{
		float outputLinear = (output.at<float>(0, index));
		complianceDegree = (int) (NetworkOutputs::sigmoid(outputLinear / temperature) * 100.0f);
		value = (complianceDegree >= 50) ? REQUIREMENT_VALUE::COMPLIANT : REQUIREMENT_VALUE::NON_COMPLIANT;
	}

	static float sigmoid(float x) 
	{
		return 1.0f / (1.0f + exp(-x));
	}
};
