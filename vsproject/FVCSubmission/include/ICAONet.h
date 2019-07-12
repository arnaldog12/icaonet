#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "DeepLearning/TensorflowGraph.h"
#include "Resource.h"

using deeplearning::TensorflowGraph;

class ICAONet
{
public:
	static int hatcap(cv::Mat imageColor)
	{
		Resource *resource = new Resource(101);
		std::ostringstream ss(resource->asString());
		TensorflowGraph *graph = new TensorflowGraph(ss);

		cv::Mat hatCapRegion = imageColor.clone();
		cv::cvtColor(hatCapRegion, hatCapRegion, CV_BGR2RGB);
		cv::resize(hatCapRegion, hatCapRegion, cv::Size(224, 224), 0.0, 0.0, CV_INTER_LINEAR);
		hatCapRegion.convertTo(hatCapRegion, CV_32F, 1.0f / 255.0f);

		TensorflowPlaceholder::tensorDict feedDict;
		feedDict.push_back(TensorflowPlaceholder::tensor("import/Placeholder:0", TensorflowUtils::mat2tensor<float>(hatCapRegion)));
		std::vector<std::vector<cv::Mat>> outputs = graph->run(feedDict, { "import/final_result:0" });

		cv::Mat scores = outputs[0][0];
		float negScore = scores.at<float>(0, 0);
		int score = (int)(negScore * 100.0f);
		return score;
	}

	static REQUIREMENT_VALUE variedBackground(cv::Mat imageColor, int& score)
	{
		Resource *resource = new Resource(101);
		std::ostringstream ss(resource->asString());
		TensorflowGraph *graph = new TensorflowGraph(ss);

		cv::Mat inputImage = imageColor.clone();
		cv::resize(inputImage, inputImage, cv::Size(224, 224), 0.0, 0.0, CV_INTER_LINEAR);
		inputImage.convertTo(inputImage, CV_32F, 1.0f / 255.0f);

		TensorflowPlaceholder::tensorDict feedDict;
		feedDict.push_back(TensorflowPlaceholder::tensor("input:0", TensorflowUtils::mat2tensor<float>(inputImage)));
		std::vector<std::vector<cv::Mat>> outputs = graph->run(feedDict, { "varied_background/Softmax:0" });
		
		double confidence;
		int yPred = softmaxClass(outputs[0][0], confidence);
		yPred = yPred - 1; // from [0, 1, 2] -> [-1, 0, 1] (nn output -> req. values)

		confidence = (yPred == 1) ? confidence : 1.0 - confidence;
		score = (int) (confidence * 100.0f);
		return (REQUIREMENT_VALUE) yPred;
	}

private:
	static int softmaxClass(cv::Mat rowMatrix, double& maxValue)
	{
		cv::Point maxLoc;
		cv::minMaxLoc(rowMatrix, NULL, &maxValue, (cv::Point *)0, &maxLoc);
		return (int) maxLoc.x;
	}
};