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
	static PhotographicRequirements* run(cv::Mat imageColor)
	{
		Resource *resource = new Resource(101);
		std::ostringstream ss(resource->asString());
		TensorflowGraph *graph = new TensorflowGraph(ss);

		cv::Mat im;
		imageColor.convertTo(im, CV_32F, 1.0f / 255.0f);
		cv::resize(im, im, cv::Size(224, 224), 0.0, 0.0, cv::INTER_AREA);

		TensorflowPlaceholder::tensorDict feedDict;
		feedDict.push_back(TensorflowPlaceholder::tensor("input:0", TensorflowUtils::mat2tensor<float>(im)));
		std::vector<std::vector<cv::Mat>> outputs = graph->run(feedDict, { "blurred/Softmax:0", "looking_away/Softmax:0", "unnatural_skin_tone/Softmax:0", "too_dark_light/Softmax:0", "washed_out/Softmax:0", "pixelation/Softmax:0", "hair_across_eyes/Softmax:0", "eyes_closed/Softmax:0", "varied_background/Softmax:0", "roll_pitch_yaw/Softmax:0", "flash_reflection_on_skin/Softmax:0", "red_eyes/Softmax:0", "shadows_behind_head/Softmax:0", "shadows_across_face/Softmax:0", "dark_tinted_lenses/Softmax:0", "flash_reflection_on_lenses/Softmax:0", "frame_covering_eyes/Softmax:0", "hat_cap/Softmax:0", "veil_over_face/Softmax:0", "mouth_open/Softmax:0", "presence_of_other_faces_or_toys/Softmax:0" });

		PhotographicRequirements *reqs = new PhotographicRequirements();

		parseTernaryOutput(outputs[0][0], reqs->blurred->value, reqs->blurred->complianceDegree);
		parseTernaryOutput(outputs[1][0], reqs->lookingAway->value, reqs->lookingAway->complianceDegree);
		parseTernaryOutput(outputs[2][0], reqs->unnaturalSkinTone->value, reqs->unnaturalSkinTone->complianceDegree);
		parseTernaryOutput(outputs[3][0], reqs->tooDarkLight->value, reqs->tooDarkLight->complianceDegree);
		parseTernaryOutput(outputs[4][0], reqs->washedOut->value, reqs->washedOut->complianceDegree);
		parseCompliantNonCompliantOutput(outputs[5][0], reqs->pixelation->value, reqs->pixelation->complianceDegree);
		parseTernaryOutput(outputs[6][0], reqs->hairAcrossEyes->value, reqs->hairAcrossEyes->complianceDegree);
		parseTernaryOutput(outputs[7][0], reqs->eyesClosed->value, reqs->eyesClosed->complianceDegree);
		parseTernaryOutput(outputs[8][0], reqs->variedBackground->value, reqs->variedBackground->complianceDegree);
		parseTernaryOutput(outputs[9][0], reqs->rollPitchYaw->value, reqs->rollPitchYaw->complianceDegree);
		parseTernaryOutput(outputs[10][0], reqs->flashReflectionOnSkin->value, reqs->flashReflectionOnSkin->complianceDegree);
		parseTernaryOutput(outputs[11][0], reqs->redEyes->value, reqs->redEyes->complianceDegree);
		parseTernaryOutput(outputs[12][0], reqs->shadowsBehindHead->value, reqs->shadowsBehindHead->complianceDegree);
		parseTernaryOutput(outputs[13][0], reqs->shadowsAcrossFace->value, reqs->shadowsAcrossFace->complianceDegree);
		parseTernaryOutput(outputs[14][0], reqs->darkTintedLenses->value, reqs->darkTintedLenses->complianceDegree);
		parseTernaryOutput(outputs[15][0], reqs->flashReflectionOnLenses->value, reqs->flashReflectionOnLenses->complianceDegree);
		parseTernaryOutput(outputs[16][0], reqs->frameCoveringEyes->value, reqs->frameCoveringEyes->complianceDegree);
		parseTernaryOutput(outputs[17][0], reqs->hatCap->value, reqs->hatCap->complianceDegree);
		parseCompliantNonCompliantOutput(outputs[18][0], reqs->veilOverFace->value, reqs->veilOverFace->complianceDegree);
		parseTernaryOutput(outputs[19][0], reqs->mouthOpen->value, reqs->mouthOpen->complianceDegree);
		parseCompliantDummyOutput(outputs[20][0], reqs->presenceOfOtherFacesOrToys->value, reqs->presenceOfOtherFacesOrToys->complianceDegree);

		return reqs;
	}

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
		
		double confidence = outputs[0][0].at<float>(0, 2);
		score = (int) (confidence * 100.0f);
		return (REQUIREMENT_VALUE) REQUIREMENT_VALUE::COMPLIANT;
	}

private:
	static void parseCompliantNonCompliantOutput(cv::Mat output, REQUIREMENT_VALUE& value, int& complianceDegree)
	{
		cv::Point maxLoc;
		cv::minMaxLoc(output, NULL, NULL, (cv::Point *)0, &maxLoc);

		value = (REQUIREMENT_VALUE) maxLoc.x; 
		complianceDegree = (int)(output.at<float>(0, 1) * 100.0f);
	}

	static void parseCompliantDummyOutput(cv::Mat output, REQUIREMENT_VALUE& value, int& complianceDegree)
	{
		cv::Point maxLoc;
		cv::minMaxLoc(output, NULL, NULL, (cv::Point *)0, &maxLoc);

		value = maxLoc.x == 0 ? REQUIREMENT_VALUE::DUMMY : REQUIREMENT_VALUE::COMPLIANT;
		complianceDegree = (value == REQUIREMENT_VALUE::DUMMY) ? 0 : (int)(output.at<float>(0, 1) * 100.0f);
	}

	static void parseTernaryOutput(cv::Mat output, REQUIREMENT_VALUE& value, int& complianceDegree)
	{
		cv::Point maxLoc;
		cv::minMaxLoc(output, NULL, NULL, (cv::Point *)0, &maxLoc);

		value = (REQUIREMENT_VALUE) (maxLoc.x - 1); // from [0, 1, 2] -> [-1, 0, 1] (nn output -> req. values)
		complianceDegree = (value == REQUIREMENT_VALUE::DUMMY) ? 0 : (int) (output.at<float>(0, 2) * 100.0f);
	}
};