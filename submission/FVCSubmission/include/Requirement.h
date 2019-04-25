#pragma once

#include <iostream>

enum REQUIREMENT_VALUE
{
	DUMMY = -1,
	NON_COMPLIANT = 0,
	COMPLIANT = 1
};

class Requirement
{
public:
	int id;
	std::string description;
	REQUIREMENT_VALUE value;

	Requirement() {}

	Requirement(int id, std::string description, REQUIREMENT_VALUE value)
	{
		this->id = id;
		this->description = description;
		this->value = value;
	}

	~Requirement(){}

	std::string toString()
	{
		return cv::format("[%02d] %s %d", this->id, this->description.c_str(), this->value);
	}
};