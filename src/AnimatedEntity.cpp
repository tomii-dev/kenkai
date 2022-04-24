#include <iostream>
#include <math.h>

#include "Tools.hpp"
#include "Properties.hpp"
#include "AnimatedEntity.hpp"

AnimatedEntity::AnimatedEntity() {
	animFrame = 0;
	frameGap = floor(Properties::frameRate / 4);
	up = false;
	down = false;
	left = false;
	right = false;
}

void AnimatedEntity::Setup() {
	Entity::Setup();
	setAnims(Tools::GetAnimsById(name));
}

void AnimatedEntity::ResetValues() {
	nextAnimFrame = frameGap;
	animFrame = 0;
}

void AnimatedEntity::setAnims(Tools::AnimationInfo _anims){
	anims = _anims;
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