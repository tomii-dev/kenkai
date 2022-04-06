#pragma once

#include "Entity.hpp"
#include "Tools.hpp"

#include "SFML/Graphics.hpp"

class AnimatedEntity : public Entity {
	Tools::AnimationInfo anims;
	void AnimUpdate() override;
	void ResetValues();
	int frameGap;
	int animFrame;
	int nextAnimFrame;
public:
	AnimatedEntity();
	void setAnims(Tools::AnimationInfo anims);
};