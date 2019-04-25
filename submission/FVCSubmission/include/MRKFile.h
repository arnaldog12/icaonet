#pragma once
#include <iostream>
#include <fstream>
#include "Eye.h"
#include "PhotographicRequirements.h"

class MRKFile
{
public:
	Eye *rightEye;
	Eye *leftEye;
	PhotographicRequirements *reqs;

	MRKFile()
	{
		this->rightEye = new Eye(cv::Point(1, 1), cv::Point(1, 1));
		this->leftEye = new Eye(cv::Point(1, 1), cv::Point(1, 1));
		this->reqs = new PhotographicRequirements();
	}

	~MRKFile() 
	{
		delete this->rightEye;
		delete this->leftEye;
		delete reqs;
	}

	void save(std::string filePath)
	{

	}

	std::string toString()
	{
		std::stringstream ss;
		ss << cv::format("Right eye => %s", this->rightEye->toString().c_str()) << "\n";
		ss << cv::format(" Left eye => %s", this->leftEye->toString().c_str()) << "\n";
		ss << this->reqs->toString() << "\n";
		return ss.str();
	}
};