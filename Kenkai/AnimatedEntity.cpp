#include <iostream>
#include <math.h>

#include "Properties.hpp"
#include "AnimatedEntity.hpp"

AnimatedEntity::AnimatedEntity() {
	frame = 0;
	animFrame = 0;
	frameGap = floor(Properties::frameRate / 6);
	up = false;
	down = false;
	left = false;
	right = false;
}

void AnimatedEntity::ResetValues() {
	frame = 0;
	nextAnimFrame = frameGap;
	animFrame = 0;
}

void AnimatedEntity::setAnims(Tools::AnimationInfo _anims){
	anims = _anims;
}

void AnimatedEntity::AnimUpdate(){
	frame++;
	if(frame == nextAnimFrame){
		nextAnimFrame += frameGap;
		animFrame++;
	}
	sprite.setTexture(anims.idleAnim[animFrame]);
	if (frame == Properties::frameRate - 1) ResetValues();
}