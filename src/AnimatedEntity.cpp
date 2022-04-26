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

void AnimatedEntity::PlayAnim(std::string id) {
	
}

void AnimatedEntity::Setup() {
	Entity::Setup();
	Tools::SetupAnimsFor(*this);
}

void AnimatedEntity::ResetValues() {
	nextAnimFrame = frameGap;
	animFrame = 0;
}

void AnimatedEntity::setAnims(std::map<std::string, Tools::Animation> anims){
	this->anims = anims;
	//frameGap = floor(Properties::frameRate / anims);
}

void AnimatedEntity::AnimUpdate(){
	/*if (velocity == sf::Vector2f()) sprite.setTexture(anims.idleAnim[animFrame]);
	if (velocity.x < 0) sprite.setTexture(anims.leftAnim[animFrame]);
	if (velocity.x > 0) sprite.setTexture(anims.rightAnim[animFrame]);
	if (Game::frame == 0) ResetValues();*/
}