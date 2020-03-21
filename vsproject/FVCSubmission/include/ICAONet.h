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
		std::vector<std::vector<cv::Mat>> outputs = graph->run(feedDict, { "blurred/Sigmoid:0", "looking_away/Sigmoid:0", "ink_marked_creased/Sigmoid:0", "unnatural_skin_tone/Sigmoid:0", "too_dark_light/Sigmoid:0", "washed_out/Sigmoid:0", "pixelation/Sigmoid:0", "hair_across_eyes/Sigmoid:0", "eyes_closed/Sigmoid:0", "varied_background/Sigmoid:0", "roll_pitch_yaw/Sigmoid:0", "flash_reflection_on_skin/Sigmoid:0", "red_eyes/Sigmoid:0", "shadows_behind_head/Sigmoid:0", "shadows_across_face/Sigmoid:0", "dark_tinted_lenses/Sigmoid:0", "flash_reflection_on_lenses/Sigmoid:0", "frames_too_heavy/Sigmoid:0", "frame_covering_eyes/Sigmoid:0", "hat_cap/Sigmoid:0", "veil_over_face/Sigmoid:0", "mouth_open/Sigmoid:0", "presence_of_other_faces_or_toys/Sigmoid:0" });

		//for (std::vector<cv::Mat> output : outputs)
		//	std::cout << output[0] << std::endl;

		PhotographicRequirements *reqs = new PhotographicRequirements();

		parseSigmoidOutput(outputs[0][0], reqs->blurred->value, reqs->blurred->complianceDegree);
		parseSigmoidOutput(outputs[1][0], reqs->lookingAway->value, reqs->lookingAway->complianceDegree);
		parseSigmoidOutput(outputs[2][0], reqs->inkMarkedCreased->value, reqs->inkMarkedCreased->complianceDegree);
		parseSigmoidOutput(outputs[3][0], reqs->unnaturalSkinTone->value, reqs->unnaturalSkinTone->complianceDegree);
		parseSigmoidOutput(outputs[4][0], reqs->tooDarkLight->value, reqs->tooDarkLight->complianceDegree);
		parseSigmoidOutput(outputs[5][0], reqs->washedOut->value, reqs->washedOut->complianceDegree);
		parseSigmoidOutput(outputs[6][0], reqs->pixelation->value, reqs->pixelation->complianceDegree);
		parseSigmoidOutput(outputs[7][0], reqs->hairAcrossEyes->value, reqs->hairAcrossEyes->complianceDegree);
		parseSigmoidOutput(outputs[8][0], reqs->eyesClosed->value, reqs->eyesClosed->complianceDegree);
		parseSigmoidOutput(outputs[9][0], reqs->variedBackground->value, reqs->variedBackground->complianceDegree);
		parseSigmoidOutput(outputs[10][0], reqs->rollPitchYaw->value, reqs->rollPitchYaw->complianceDegree);
		parseSigmoidOutput(outputs[11][0], reqs->flashReflectionOnSkin->value, reqs->flashReflectionOnSkin->complianceDegree);
		parseSigmoidOutput(outputs[12][0], reqs->redEyes->value, reqs->redEyes->complianceDegree);
		parseSigmoidOutput(outputs[13][0], reqs->shadowsBehindHead->value, reqs->shadowsBehindHead->complianceDegree);
		parseSigmoidOutput(outputs[14][0], reqs->shadowsAcrossFace->value, reqs->shadowsAcrossFace->complianceDegree);
		parseSigmoidOutput(outputs[15][0], reqs->darkTintedLenses->value, reqs->darkTintedLenses->complianceDegree);
		parseSigmoidOutput(outputs[16][0], reqs->flashReflectionOnLenses->value, reqs->flashReflectionOnLenses->complianceDegree);
		parseSigmoidOutput(outputs[17][0], reqs->framesTooHeavy->value, reqs->framesTooHeavy->complianceDegree);
		parseSigmoidOutput(outputs[18][0], reqs->frameCoveringEyes->value, reqs->frameCoveringEyes->complianceDegree);
		parseSigmoidOutput(outputs[19][0], reqs->hatCap->value, reqs->hatCap->complianceDegree);
		parseSigmoidOutput(outputs[20][0], reqs->veilOverFace->value, reqs->veilOverFace->complianceDegree);
		parseSigmoidOutput(outputs[21][0], reqs->mouthOpen->value, reqs->mouthOpen->complianceDegree);
		parseSigmoidOutput(outputs[22][0], reqs->presenceOfOtherFacesOrToys->value, reqs->presenceOfOtherFacesOrToys->complianceDegree);

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

		value = (REQUIREMENT_VALUE)maxLoc.x;
		complianceDegree = (value == REQUIREMENT_VALUE::NON_COMPLIANT) ? (int) ((1.0f - output.at<float>(0, 0))*100.0f) : (int) (output.at<float>(0, 1)*100.0f);
	}

	static void parseSigmoidOutput(cv::Mat output, REQUIREMENT_VALUE& value, int& complianceDegree)
	{
		cv::Point maxLoc;
		cv::minMaxLoc(output, NULL, NULL, (cv::Point *)0, &maxLoc);

		value = (REQUIREMENT_VALUE)maxLoc.x;
		complianceDegree = (int)(output.at<float>(0, 0) * 100.0f);
	}

	static void parseTernaryOutput(cv::Mat output, REQUIREMENT_VALUE& value, int& complianceDegree)
	{
		cv::Point maxLoc;
		cv::minMaxLoc(output, NULL, NULL, (cv::Point *)0, &maxLoc);

		value = (REQUIREMENT_VALUE) (maxLoc.x - 1); // from [0, 1, 2] -> [-1, 0, 1] (nn output -> req. values)
		switch (value)
		{
			case REQUIREMENT_VALUE::DUMMY: 
				value = REQUIREMENT_VALUE::NON_COMPLIANT;
				complianceDegree = (int)((1.0f - output.at<float>(0, 0)) * 100.0f); 
				break;
			case REQUIREMENT_VALUE::NON_COMPLIANT: complianceDegree = (int)((1.0f - output.at<float>(0, 1)) * 100.0f); break;
			case REQUIREMENT_VALUE::COMPLIANT: complianceDegree = (int)(output.at<float>(0, 2) * 100.0f); break;
			default: break;
		}
	}
};