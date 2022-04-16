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

#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/opencv/cv_image.h>


using deeplearning::TensorflowGraph;

#define IMAGE_SIZE cv::Size(160, 160)

class ICAONet
{
public:
	static EvaluationResults* run(cv::Mat imageColor, ErrorCode& errorCode)
	{
		EvaluationResults *results = new EvaluationResults();

		dlib::frontal_face_detector detectorDlib = dlib::get_frontal_face_detector();

		std::vector<cv::Rect> faceRects;
		cv::Mat imageRGB;
		cv::cvtColor(imageColor, imageRGB, cv::COLOR_BGR2RGB);

		dlib::cv_image<dlib::bgr_pixel> img(imageRGB);
		std::vector<dlib::rectangle> dets = detectorDlib(img, 0.0);
		
		if (dets.size() == 0)
			return results;

		dlib::rectangle faceRect = dets.at(0);
		cv::rectangle(imageColor, dlib2cv(faceRect), cv::Scalar(0, 255, 0));

		Resource *resource = new Resource(103);
		dlib::shape_predictor landmarksDetector;
		std::istringstream landmarkContent(resource->asString());
		dlib::deserialize(landmarksDetector, landmarkContent);

		dlib::full_object_detection shape = landmarksDetector(img, faceRect);

		std::vector<cv::Point> landmarks;
		std::vector<cv::Point> shapePoints = dlib2cv(shape);
		results->rightEye = new Eye(shapePoints[16], shapePoints[18]);
		results->leftEye = new Eye(shapePoints[20], shapePoints[22]);
		
		//cv::circle(imageColor, results->rightEye->leftCorner, 3, cv::Scalar(255, 0, 0));
		//cv::circle(imageColor, results->rightEye->rightCorner, 3, cv::Scalar(0, 255, 0));
		//cv::circle(imageColor, results->leftEye->leftCorner, 3, cv::Scalar(0, 0, 255));
		//cv::circle(imageColor, results->leftEye->rightCorner, 3, cv::Scalar(0, 255, 255));
		//cv::imshow("result", imageColor);
		//cv::waitKey();

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

	__inline static cv::Rect dlib2cv(dlib::rectangle& rec)
	{
		return cv::Rect(rec.left(), rec.top(), rec.width(), rec.height());
	}

	__inline static cv::Point dlib2cv(dlib::point& pt)
	{
		return cv::Point(pt.x(), pt.y());
	}

	__inline static  std::vector<cv::Point> dlib2cv(dlib::full_object_detection shape)
	{
		unsigned long size = shape.num_parts();
		std::vector<cv::Point> vec;

		for (unsigned long i = 0; i < size; i++)
			vec.push_back(dlib2cv(shape.part(i)));

		return vec;
	}
};