#pragma once

#include <iostream>

enum REQUIREMENT_VALUE
{
	DUMMY = -1,
	NON_COMPLIANT = 0,
	COMPLIANT = 1,

	UNABLE_TO_EVALUATE = 2
};

class Requirement
{
public:
	int id;
	std::string description;
	REQUIREMENT_VALUE value;
	int complianceDegree;

	Requirement() {}

	Requirement(int id, std::string description, REQUIREMENT_VALUE value = REQUIREMENT_VALUE::UNABLE_TO_EVALUATE, int complianceDegree = 0)
	{
		this->id = id;
		this->description = description;
		this->value = value;
		this->complianceDegree = complianceDegree;
	}

	~Requirement(){}

	std::string toString()
	{
		return cv::format("[%02d] %s %d %d", this->id, this->description.c_str(), this->value, this->complianceDegree);
	}
};