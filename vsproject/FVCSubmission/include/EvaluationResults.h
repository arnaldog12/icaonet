#pragma once
#include "Eye.h"
#include "PhotographicRequirements.h"

class EvaluationResults
{
public:
	Eye *rightEye;
	Eye *leftEye;
	PhotographicRequirements *photoReqs;

	EvaluationResults()
	{
		this->rightEye = new Eye();
		this->leftEye = new Eye();
		this->photoReqs = new PhotographicRequirements();
	}

	~EvaluationResults() 
	{
		delete rightEye;
		delete leftEye;
		delete photoReqs;
	}
};

