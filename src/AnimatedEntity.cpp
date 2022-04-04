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
	if (m_movement == sf::Vector2f()) sprite.setTexture(anims.idleAnim[animFrame]);
	if (m_movement == sf::Vector2f(-1, 0)) sprite.setTexture(anims.leftAnim[animFrame]);
	if (m_movement == sf::Vector2f(1, 0)) sprite.setTexture(anims.rightAnim[animFrame]);
 	
	if (frame == Properties::frameRate - 1) ResetValues();
}