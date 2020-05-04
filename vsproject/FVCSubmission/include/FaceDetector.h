#pragma once

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "DeepLearning/TensorflowGraph.h"
#include "Resource.h"

using deeplearning::TensorflowGraph;

class FaceDetector
{
public:
	static cv::Rect run(cv::Mat bgrImage, float scoreThreshold = 0.1f)
	{
		Resource *resource = new Resource(102);
		std::ostringstream ss(resource->asString());
		TensorflowGraph *graph = new TensorflowGraph(ss);

		cv::Mat img;
		cv::cvtColor(bgrImage, img, cv::COLOR_BGR2RGB);
		img.convertTo(img, CV_8UC3);

		TensorflowPlaceholder::tensorDict feedDict;
		feedDict.push_back(TensorflowPlaceholder::tensor("image_tensor:0", TensorflowUtils::mat2tensor<uchar>(img, DT_UINT8)));

		std::vector<std::vector<cv::Mat>> outputs = graph->run(feedDict, { "detection_boxes:0", "detection_scores:0"/*, "detection_classes:0", "num_detections:0"*/ });
		cv::Mat boxes = outputs[0][0];
		cv::Mat scores = outputs[1][0];

		cv::Rect rect = getHighestScoreRect(img.size(), boxes, scores, scoreThreshold);
		return rect;
	}

private:
	static cv::Rect getHighestScoreRect(cv::Size imSize, cv::Mat boxes, cv::Mat scores, float confThreshold = 0.1f)
	{
		int width = imSize.width, height = imSize.height;
		int nBoxes = boxes.rows;

		cv::Rect bestRect;
		float yMinRel, xMinRel, yMaxRel, xMaxRel, bestScore = 0.0;
		for (int i = 0; i < nBoxes; i++)
		{
			float score = scores.at<float>(0, i);
			if (score <= confThreshold)
				continue;

			if (score > bestScore)
			{
				yMinRel = boxes.at<float>(i, 0);
				xMinRel = boxes.at<float>(i, 1);
				yMaxRel = boxes.at<float>(i, 2);
				xMaxRel = boxes.at<float>(i, 3);

				cv::Point upper((int)(width*xMinRel), (int)(height*yMinRel));
				cv::Point lower((int)(width*xMaxRel), (int)(height*yMaxRel));

				bestRect = cv::Rect(upper, lower);
				bestScore = score;
			}
		}

		return bestRect;
	}
};

