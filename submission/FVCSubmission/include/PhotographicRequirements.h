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
		this->blurred = new Requirement(1, "Blurred");
		this->lookingAway = new Requirement(2, "Looking away");
		this->inkMarkedCreased = new Requirement(3, "Ink marked/creased");
		this->unnaturalSkinTone = new Requirement(4, "Unnatural skin tone");
		this->tooDarkLight = new Requirement(5, "Too dark/light");
		this->washedOut = new Requirement(6, "Washed out");
		this->pixelation = new Requirement(7, "Pixelation");
		this->hairAcrossEyes = new Requirement(8, "Hair across eyes");
		this->eyesClosed = new Requirement(9, "Eyes closed");
		this->variedBackground = new Requirement(10, "Varied background");
		this->rollPitchYaw = new Requirement(11, "Roll/pitch/yaw rotations greater than a predefined thresholds");
		this->flashReflectionOnSkin = new Requirement(12, "Flash reflection on skin");
		this->redEyes = new Requirement(13, "Red eyes");
		this->shadowsBehindHead = new Requirement(14, "Shadows behind head");
		this->shadowsAcrossFace = new Requirement(15, "Shadows across face");
		this->darkTintedLenses = new Requirement(16, "Dark tinted lenses");
		this->flashReflectionOnLenses = new Requirement(17, "Flash reflection on lenses");
		this->framesTooHeavy = new Requirement(18, "Frames too heavy");
		this->frameCoveringEyes = new Requirement(19, "Frame covering eyes");
		this->hatCap = new Requirement(20, "Hat/cap");
		this->veilOverFace = new Requirement(21, "Veil over face");
		this->mouthOpen = new Requirement(22, "Mouth open");
		this->presenceOfOtherFacesOrToys = new Requirement(23, "Presence of other faces or toys too close to face");
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
