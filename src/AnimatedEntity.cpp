#include <iostream>
#include <math.h>

#include "Tools.hpp"
#include "Properties.hpp"
#include "AnimatedEntity.hpp"

AnimatedEntity::AnimatedEntity() {
	frame = 0;
	animFrame = 0;
	overrideAnimCount = 0;
	up = false;
	down = false;
	left = false;
	right = false;
	lastAnimId = "";
}

void AnimatedEntity::setFrameGap(std::string id) {
	std::map<std::string, Tools::Animation>::iterator it;
	for (it = anims.begin(); it != anims.end(); it++)
		if (it->second.name == id)
			frameGap = floor(Properties::frameRate / it->second.count);
	ResetValues();
}

void AnimatedEntity::setAnim(std::string id) {
	if (override) return;
	std::map<std::string, Tools::Animation>::iterator it;
	for (it = anims.begin(); it != anims.end(); it++)
		if (it->second.name == id)
			overrideAnimCount = it->second.count-1;
	animId = id;
	override = 1;
}

void AnimatedEntity::PlayAnim(std::string id) {
	frame++;
	if (frame == nextAnimFrame) {
		nextAnimFrame += frameGap;
		animFrame++;
		if (override) overrideAnimCount--;
	}
	std::map<std::string, Tools::Animation>::iterator it;
	for (it = anims.begin(); it != anims.end(); it++)
		if (it->second.name == id)
			sprite.setTexture(it->second.frames[animFrame]);
	if (override) return;
	if (frame == Properties::frameRate - 1) ResetValues();
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
	std::string animId;
	if (velocity == sf::Vector2f()) animId = "idle";
	if (velocity.x < 0) animId = "walkLeft";
	if (velocity.x > 0) animId = "walkRight";
	if (override) {
		if (!overrideAnimCount) override = 0;
		else animId = this->animId;
	}
	if(animId != lastAnimId)
		setFrameGap(animId);
	PlayAnim(animId);
	lastAnimId = animId;
}