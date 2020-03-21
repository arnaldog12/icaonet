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
		delete outputs;

		//std::vector<Requirement *> listReqs = reqs->getRequirements();
		//for (int i = 0; i < graphOutputs.size(); i++)
		//{
		//	std::cout << graphOutputs[i][0] << " ";
		//	std::cout << listReqs[i]->complianceDegree;
		//	std::cout << std::endl;
		//}

		return reqs;
	}

private:
	static NetworkOutputs* initNetworkOutputs(PhotographicRequirements* &reqs)
	{
		NetworkOutputs *outputs = new NetworkOutputs();
		outputs->addOutput(new NetworkOutput("blurred/Sigmoid:0", reqs->blurred));
		outputs->addOutput(new NetworkOutput("looking_away/Sigmoid:0", reqs->lookingAway));
		outputs->addOutput(new NetworkOutput("ink_marked_creased/Sigmoid:0", reqs->inkMarkedCreased));
		outputs->addOutput(new NetworkOutput("unnatural_skin_tone/Sigmoid:0", reqs->unnaturalSkinTone));
		outputs->addOutput(new NetworkOutput("too_dark_light/Sigmoid:0", reqs->tooDarkLight));
		outputs->addOutput(new NetworkOutput("washed_out/Sigmoid:0", reqs->washedOut));
		outputs->addOutput(new NetworkOutput("pixelation/Sigmoid:0", reqs->pixelation));
		outputs->addOutput(new NetworkOutput("hair_across_eyes/Sigmoid:0", reqs->hairAcrossEyes));
		outputs->addOutput(new NetworkOutput("eyes_closed/Sigmoid:0", reqs->eyesClosed));
		outputs->addOutput(new NetworkOutput("varied_background/Sigmoid:0", reqs->variedBackground));
		outputs->addOutput(new NetworkOutput("roll_pitch_yaw/Sigmoid:0", reqs->rollPitchYaw));
		outputs->addOutput(new NetworkOutput("flash_reflection_on_skin/Sigmoid:0", reqs->flashReflectionOnSkin));
		outputs->addOutput(new NetworkOutput("red_eyes/Sigmoid:0", reqs->redEyes));
		outputs->addOutput(new NetworkOutput("shadows_behind_head/Sigmoid:0", reqs->shadowsBehindHead));
		outputs->addOutput(new NetworkOutput("shadows_across_face/Sigmoid:0", reqs->shadowsAcrossFace));
		outputs->addOutput(new NetworkOutput("dark_tinted_lenses/Sigmoid:0", reqs->darkTintedLenses));
		outputs->addOutput(new NetworkOutput("flash_reflection_on_lenses/Sigmoid:0", reqs->flashReflectionOnLenses));
		outputs->addOutput(new NetworkOutput("frames_too_heavy/Sigmoid:0", reqs->framesTooHeavy));
		outputs->addOutput(new NetworkOutput("frame_covering_eyes/Sigmoid:0", reqs->frameCoveringEyes));
		outputs->addOutput(new NetworkOutput("hat_cap/Sigmoid:0", reqs->hatCap));
		outputs->addOutput(new NetworkOutput("veil_over_face/Sigmoid:0", reqs->veilOverFace));
		outputs->addOutput(new NetworkOutput("mouth_open/Sigmoid:0", reqs->mouthOpen));
		outputs->addOutput(new NetworkOutput("presence_of_other_faces_or_toys/Sigmoid:0", reqs->presenceOfOtherFacesOrToys));
		return outputs;
	}
};