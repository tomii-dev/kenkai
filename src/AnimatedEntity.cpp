#include <iostream>
#include <math.h>

#include "Tools.hpp"
#include "Properties.hpp"
#include "AnimatedEntity.hpp"

AnimatedEntity::AnimatedEntity() {
	animFrame = 0;
	up = false;
	down = false;
	left = false;
	right = false;
}

void AnimatedEntity::PlayAnim() {
	
}

void AnimatedEntity::Setup() {
	Entity::Setup();
	setAnims(Tools::GetAnimsById(name));
}

void AnimatedEntity::ResetValues() {
	nextAnimFrame = frameGap;
	animFrame = 0;
}

void AnimatedEntity::setAnims(Tools::AnimationInfo anims){
	this->anims = anims;
	frameGap = floor(Properties::frameRate / anims.count);
}

void AnimatedEntity::AnimUpdate(){
	if(Game::frame == nextAnimFrame){
		nextAnimFrame += frameGap;
		animFrame++;
	}
	if (velocity == sf::Vector2f()) sprite.setTexture(anims.idleAnim[animFrame]);
	if (velocity.x < 0) sprite.setTexture(anims.leftAnim[animFrame]);
	if (velocity.x > 0) sprite.setTexture(anims.rightAnim[animFrame]);
	if (Game::frame == 0) ResetValues();
}