#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "DeepLearning/TensorflowGraph.h"

using deeplearning::TensorflowGraph;

class ICAONet
{
public:
	static int hatcap(cv::Mat imageColor)
	{
		const static string fileGraph = "hatcap_classifier_v1.pb";
		TensorflowGraph *graph = new TensorflowGraph(fileGraph);

		cv::Point rightEye, leftEye;
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

private:
};