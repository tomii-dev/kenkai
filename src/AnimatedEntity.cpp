#include <iostream>
#include <math.h>

#include "Tools.hpp"
#include "Properties.hpp"
#include "AnimatedEntity.hpp"

AnimatedEntity::AnimatedEntity()
	: frame				(0),
	  animFrame			(0),
	  maxFrame			(0),
	  lastAnimId		(""),
	  overrideAnimId	("")
{}

void AnimatedEntity::SetValues(std::string id) {
	Tools::Animation anim;
	std::map<std::string, Tools::Animation>::iterator it;
	for (it = anims.begin(); it != anims.end(); it++)
		if (it->second.name == id) 
			anim = it->second;
	if (anim.duration > 0) maxFrame = Tools::getFrames(anim.duration);
	else maxFrame = Tools::getFrames(Properties::frameRate);
	frameGap = floor(maxFrame / anim.count);
 	ResetValues();
}

void AnimatedEntity::setAnim(std::string id, bool playFull) {
	if (playFull) {
		override = true;
		overrideAnimId = id;
	}
	else animId = id;
}

void AnimatedEntity::PlayAnim(std::string id) {
	if (override) id = overrideAnimId;
	frame++;
	if (frame == nextAnimFrame) {
		nextAnimFrame += frameGap;
		animFrame++;
	}
	std::map<std::string, Tools::Animation>::iterator it;
	for (it = anims.begin(); it != anims.end(); it++)
		if (it->second.name == id)
			sprite.setTexture(it->second.frames[animFrame]);
	if (frame == maxFrame - 1) {
		if (override) override = false;
		ResetValues();
	}
}

void AnimatedEntity::Setup() {
	Entity::Setup();
	Tools::SetupAnimsFor(this);
}

void AnimatedEntity::ResetValues() {
	frame = 0;
	nextAnimFrame = frameGap;
	animFrame = 0;
}

void AnimatedEntity::setAnims(std::map<std::string, Tools::Animation> anims){
	this->anims = anims;
}

void AnimatedEntity::AnimUpdate(){
	if(animId != lastAnimId) SetValues(animId);
	PlayAnim(animId);
	lastAnimId = animId;
}