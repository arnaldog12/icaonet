#pragma once
#include "Requirement.h"
#include <vector>

class PhotographicRequirements : public Requirement
{
public:		   
	Requirement* blurred;
	Requirement* lookingAway;
	Requirement* inkMarkedCreased;
	Requirement* unnaturalSkinTone;
	Requirement* tooDarkLight;
	Requirement* washedOut;
	Requirement* pixelation;
	Requirement* hairAcrossEyes;
	Requirement* eyesClosed;
	Requirement* variedBackground;
	Requirement* rollPitchYaw;
	Requirement* flashReflectionOnSkin;
	Requirement* redEyes;
	Requirement* shadowsBehindHead;
	Requirement* shadowsAcrossFace;
	Requirement* darkTintedLenses;
	Requirement* flashReflectionOnLenses;
	Requirement* framesTooHeavy;
	Requirement* frameCoveringEyes;
	Requirement* hatCap;
	Requirement* veilOverFace;
	Requirement* mouthOpen;
	Requirement* presenceOfOtherFacesOrToys;

private:
	std::vector<Requirement *> listReqs;

public:
	PhotographicRequirements() : listReqs(23)
	{
		this->blurred = new Requirement(1, "Blurred", REQUIREMENT_VALUE::DUMMY);
		this->lookingAway = new Requirement(2, "Looking away", REQUIREMENT_VALUE::DUMMY);
		this->inkMarkedCreased = new Requirement(3, "Ink marked/creased", REQUIREMENT_VALUE::DUMMY);
		this->unnaturalSkinTone = new Requirement(4, "Unnatural skin tone", REQUIREMENT_VALUE::DUMMY);
		this->tooDarkLight = new Requirement(5, "Too dark/light", REQUIREMENT_VALUE::DUMMY);
		this->washedOut = new Requirement(6, "Washed out", REQUIREMENT_VALUE::DUMMY);
		this->pixelation = new Requirement(7, "Pixelation", REQUIREMENT_VALUE::DUMMY);
		this->hairAcrossEyes = new Requirement(8, "Hair across eyes", REQUIREMENT_VALUE::DUMMY);
		this->eyesClosed = new Requirement(9, "Eyes closed", REQUIREMENT_VALUE::DUMMY);
		this->variedBackground = new Requirement(10, "Varied background", REQUIREMENT_VALUE::DUMMY);
		this->rollPitchYaw = new Requirement(11, "Roll/pitch/yaw rotations greater than a predefined thresholds", REQUIREMENT_VALUE::DUMMY);
		this->flashReflectionOnSkin = new Requirement(12, "Flash reflection on skin", REQUIREMENT_VALUE::DUMMY);
		this->redEyes = new Requirement(13, "Red eyes", REQUIREMENT_VALUE::DUMMY);
		this->shadowsBehindHead = new Requirement(14, "Shadows behind head", REQUIREMENT_VALUE::DUMMY);
		this->shadowsAcrossFace = new Requirement(15, "Shadows across face", REQUIREMENT_VALUE::DUMMY);
		this->darkTintedLenses = new Requirement(16, "Dark tinted lenses", REQUIREMENT_VALUE::DUMMY);
		this->flashReflectionOnLenses = new Requirement(17, "Flash reflection on lenses", REQUIREMENT_VALUE::DUMMY);
		this->framesTooHeavy = new Requirement(18, "Frames too heavy", REQUIREMENT_VALUE::DUMMY);
		this->frameCoveringEyes = new Requirement(19, "Frame covering eyes", REQUIREMENT_VALUE::DUMMY);
		this->hatCap = new Requirement(20, "Hat/cap", REQUIREMENT_VALUE::DUMMY);
		this->veilOverFace = new Requirement(21, "Veil over face", REQUIREMENT_VALUE::DUMMY);
		this->mouthOpen = new Requirement(22, "Mouth open", REQUIREMENT_VALUE::DUMMY);
		this->presenceOfOtherFacesOrToys = new Requirement(23, "Presence of other faces or toys too close to face", REQUIREMENT_VALUE::DUMMY);
		this->listReqs = { this->blurred, this->lookingAway, this->inkMarkedCreased, this->unnaturalSkinTone, this->tooDarkLight, this->washedOut, this->pixelation, this->hairAcrossEyes, this->eyesClosed, this->variedBackground, this->rollPitchYaw, this->flashReflectionOnSkin, this->redEyes, this->shadowsBehindHead, this->shadowsAcrossFace, this->darkTintedLenses, this->flashReflectionOnLenses, this->framesTooHeavy, this->frameCoveringEyes, this->hatCap, this->veilOverFace, this->mouthOpen, this->presenceOfOtherFacesOrToys };
	}

	~PhotographicRequirements() 
	{
		delete blurred;
		delete lookingAway;
		delete inkMarkedCreased;
		delete unnaturalSkinTone;
		delete tooDarkLight;
		delete washedOut;
		delete pixelation;
		delete hairAcrossEyes;
		delete eyesClosed;
		delete variedBackground;
		delete rollPitchYaw;
		delete flashReflectionOnSkin;
		delete redEyes;
		delete shadowsBehindHead;
		delete shadowsAcrossFace;
		delete darkTintedLenses;
		delete flashReflectionOnLenses;
		delete framesTooHeavy;
		delete frameCoveringEyes;
		delete hatCap;
		delete veilOverFace;
		delete mouthOpen;
		delete presenceOfOtherFacesOrToys;

		std::vector<Requirement *>().swap(this->listReqs);
	}

	std::vector<Requirement *> getRequirements()
	{
		return this->listReqs;
	}

	std::string toString()
	{
		std::stringstream ss;
		for (Requirement *req : this->listReqs)
			ss << req->toString() << "\n";
		return ss.str();
	}
};
