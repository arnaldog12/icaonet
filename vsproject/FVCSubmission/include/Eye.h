#pragma once
#include "opencv2/core/core.hpp"

class Eye
{
public:
	cv::Point leftCorner;
	cv::Point rightCorner;
	
	Eye() 
	{
		this->leftCorner = cv::Point(-1, -1);
		this->rightCorner = cv::Point(-1, -1);
	}
	
	Eye(cv::Point leftCorner, cv::Point rightCorner)
	{
		this->leftCorner = leftCorner;
		this->rightCorner = rightCorner;
	}

	~Eye() {}

	cv::Point center()
	{
		return (leftCorner + rightCorner) / 2;
	}

	std::string toString()
	{
		return cv::format("left corner: (%d, %d) right corner: (%d, %d)", 
			this->leftCorner.x, 
			this->leftCorner.y, 
			this->rightCorner.x, 
			this->rightCorner.y);
	}
};