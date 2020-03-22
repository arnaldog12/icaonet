#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "DeepLearning/TensorflowGraph.h"
#include "NetworkOutputs.h"
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

		PhotographicRequirements *reqs = new PhotographicRequirements();
		NetworkOutputs *outputs = initNetworkOutputs(reqs);

		TensorflowPlaceholder::tensorDict feedDict;
		feedDict.push_back(TensorflowPlaceholder::tensor("input:0", TensorflowUtils::mat2tensor<float>(im)));
		std::vector<std::vector<cv::Mat>> graphOutputs = graph->run(feedDict, outputs->getOutputNames());

		outputs->parse(graphOutputs);

		//std::vector<RequirementOutput *> netOutputs = outputs->vectorOutputs;
		//for (int i = 0; i < graphOutputs.size(); i++)
		//{
		//	std::cout << graphOutputs[i][0] << " ";
		//	std::cout << netOutputs[i]->requirement->complianceDegree;
		//	std::cout << std::endl;
		//}

		delete outputs;
		return reqs;
	}

private:
	static NetworkOutputs* initNetworkOutputs(PhotographicRequirements* &reqs)
	{
		NetworkOutputs *outputs = new NetworkOutputs();
		outputs->addOutput(new RequirementOutput("blurred/Sigmoid:0", reqs->blurred));
		outputs->addOutput(new RequirementOutput("looking_away/Sigmoid:0", reqs->lookingAway));
		//outputs->addOutput(new NetworkOutput("ink_marked_creased/Sigmoid:0", reqs->inkMarkedCreased));
		outputs->addOutput(new RequirementOutput("unnatural_skin_tone/Sigmoid:0", reqs->unnaturalSkinTone));
		outputs->addOutput(new RequirementOutput("too_dark_light/Sigmoid:0", reqs->tooDarkLight));
		outputs->addOutput(new RequirementOutput("washed_out/Sigmoid:0", reqs->washedOut));
		outputs->addOutput(new RequirementOutput("pixelation/Sigmoid:0", reqs->pixelation));
		outputs->addOutput(new RequirementOutput("hair_across_eyes/Sigmoid:0", reqs->hairAcrossEyes));
		outputs->addOutput(new RequirementOutput("eyes_closed/Sigmoid:0", reqs->eyesClosed));
		outputs->addOutput(new RequirementOutput("varied_background/Sigmoid:0", reqs->variedBackground));
		outputs->addOutput(new RequirementOutput("roll_pitch_yaw/Sigmoid:0", reqs->rollPitchYaw));
		outputs->addOutput(new RequirementOutput("flash_reflection_on_skin/Sigmoid:0", reqs->flashReflectionOnSkin));
		outputs->addOutput(new RequirementOutput("red_eyes/Sigmoid:0", reqs->redEyes));
		outputs->addOutput(new RequirementOutput("shadows_behind_head/Sigmoid:0", reqs->shadowsBehindHead));
		outputs->addOutput(new RequirementOutput("shadows_across_face/Sigmoid:0", reqs->shadowsAcrossFace));
		outputs->addOutput(new RequirementOutput("dark_tinted_lenses/Sigmoid:0", reqs->darkTintedLenses));
		outputs->addOutput(new RequirementOutput("flash_reflection_on_lenses/Sigmoid:0", reqs->flashReflectionOnLenses));
		outputs->addOutput(new RequirementOutput("frames_too_heavy/Sigmoid:0", reqs->framesTooHeavy));
		outputs->addOutput(new RequirementOutput("frame_covering_eyes/Sigmoid:0", reqs->frameCoveringEyes));
		outputs->addOutput(new RequirementOutput("hat_cap/Sigmoid:0", reqs->hatCap));
		outputs->addOutput(new RequirementOutput("veil_over_face/Sigmoid:0", reqs->veilOverFace));
		outputs->addOutput(new RequirementOutput("mouth_open/Sigmoid:0", reqs->mouthOpen));
		outputs->addOutput(new RequirementOutput("presence_of_other_faces_or_toys/Sigmoid:0", reqs->presenceOfOtherFacesOrToys));
		return outputs;
	}
};