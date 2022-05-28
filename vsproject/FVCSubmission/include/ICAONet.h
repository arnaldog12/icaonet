#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "DeepLearning/TensorflowGraph.h"
#include "EvaluationResults.h"
#include "FaceDetector.h"
#include "NetworkOutputs.h"
#include "Resource.h"

#include "opencv2/highgui/highgui.hpp" // debug only

using deeplearning::TensorflowGraph;

#define IMAGE_SIZE cv::Size(160, 160)

class ICAONet
{
public:
	static EvaluationResults* run(cv::Mat imageColor, ErrorCode& errorCode)
	{
		Resource *resource = new Resource(101);
		std::ostringstream ss(resource->asString());
		TensorflowGraph *graph = new TensorflowGraph(ss);

		EvaluationResults *results = new EvaluationResults();

		cv::Point offset;
		cv::Mat preprocessedImg = preprocessing(imageColor, errorCode, offset);
		if (errorCode != ErrorCode::SUCCESS)
			return results;

		cv::Mat im;
		cv::resize(preprocessedImg, im, IMAGE_SIZE, 0.0, 0.0, cv::INTER_AREA);
		im.convertTo(im, CV_32F, 1.0f / 255.0f);

		TensorflowPlaceholder::tensorDict feedDict;
		feedDict.push_back(TensorflowPlaceholder::tensor("input:0", TensorflowUtils::mat2tensor<float>(im)));
		std::vector<std::vector<cv::Mat>> graphOutputs = graph->run(feedDict, NetworkOutputs::getOutputNames());

		NetworkOutputs::parseRequirements(graphOutputs, results->photoReqs);
		NetworkOutputs::parseEyes(graphOutputs, results->rightEye, results->leftEye, im.size(), cv::Point(0, 0));

		//printDebug(graphOutputs, results, im);

		errorCode = ErrorCode::SUCCESS;
		return results;
	}

private:
	static cv::Mat preprocessing(cv::Mat bgrImage, ErrorCode &errorCode, cv::Point& offset)
	{
		cv::Rect faceRect = FaceDetector::run(bgrImage);
		if (faceRect.empty())
		{
			errorCode = ErrorCode::CANNOT_DETECT_FACE;
			return cv::Mat();
		}

		cv::Rect padRect(faceRect + cv::Size((int)(faceRect.width * 1.5), (int)(faceRect.height * 1.5)));
		padRect.height = std::max(padRect.height, padRect.width);
		padRect.width = std::max(padRect.height, padRect.width);

		cv::Point centerPad((int)((padRect.x + padRect.width) / 2), (int)((padRect.y + padRect.height) / 2));
		cv::Point centerFace((int)((faceRect.x + faceRect.width) / 2), (int)((faceRect.y + faceRect.height) / 2));
		cv::Point offsetCenter(centerFace.x - centerPad.x, centerFace.y - centerPad.y);
		padRect += offsetCenter;

		offset = cv::Point(padRect.tl().x, padRect.tl().y);

		int top = 0, bottom = 0, left = 0, right = 0;
		if (padRect.x < 0) left = -padRect.x;
		if (padRect.y < 0) top = -padRect.y;
		if (padRect.x + padRect.width > bgrImage.cols) right = (padRect.x + padRect.width) - bgrImage.cols;
		if (padRect.y + padRect.height > bgrImage.rows) bottom = (padRect.y + padRect.height) - bgrImage.rows;

		cv::copyMakeBorder(bgrImage, bgrImage, top, bottom, left, right, cv::BORDER_CONSTANT, cv::Scalar(0));
		padRect.x += left;
		padRect.y += top;

		errorCode = ErrorCode::SUCCESS;
		cv::Mat result = bgrImage(padRect).clone();
		return result;
	}

	static void printDebug(std::vector<std::vector<cv::Mat>> graphOutputs, EvaluationResults *results, cv::Mat image)
	{
		std::cout << "Requirements:" << std::endl;
		int nReqs = graphOutputs[0][0].size().width;
		std::vector<Requirement *> reqs = results->photoReqs->getRequirements();
		for (int i = 0; i < graphOutputs[0][0].size().width; i++) 
		{
			std::cout << graphOutputs[0][0].at<float>(0, i) << " ";
			std::cout << reqs[i]->complianceDegree;
			std::cout << std::endl;
		}

		std::cout << "\nEyes:" << std::endl;
		int nEyes = graphOutputs[1][0].size().width;
		cv::Mat eyeOutput = graphOutputs[1][0];
		for (int i = 0; i < nEyes; i++)
			std::cout << eyeOutput.at<float>(0, i) << std::endl;
		std::cout << results->rightEye->toString() << std::endl;
		std::cout << results->leftEye->toString() << std::endl;
		
		cv::circle(image, results->rightEye->leftCorner, 3, cv::Scalar(255, 0, 0));
		cv::circle(image, results->rightEye->rightCorner, 3, cv::Scalar(0, 255, 0));
		cv::circle(image, results->leftEye->leftCorner, 3, cv::Scalar(0, 0, 255));
		cv::circle(image, results->leftEye->rightCorner, 3, cv::Scalar(0, 255, 255));
		cv::imshow("result", image);
		cv::waitKey();
	}
};