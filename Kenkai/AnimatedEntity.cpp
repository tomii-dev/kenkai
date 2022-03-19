#include <iostream>
#include <math.h>

#include "Properties.hpp"
#include "AnimatedEntity.hpp"

AnimatedEntity::AnimatedEntity(float x, float y) {
	frame = 0;
	frameCount = 0;
	animFrame = 0;
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

void AnimatedEntity::setTextures(sf::Texture* textures){
	for (int i = 0; i < Properties::frameRate; i++) {
		if (textures[i].getSize().x == 0) break;

		frames[i] = textures[i];
		frameCount++;
	}
	frameGap = floor(Properties::frameRate / frameCount);
	nextAnimFrame = frameGap;
}

void AnimatedEntity::AnimUpdate(){
	frame++;
	if(frame == nextAnimFrame){
		nextAnimFrame += frameGap;
		animFrame++;
	}
	sprite.setTexture(frames[animFrame]);
	if (frame == Properties::frameRate - 1) ResetValues();
}