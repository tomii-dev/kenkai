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
protected:
	void PlayAnim();
	void Setup() override;
public:
	AnimatedEntity();
	void setAnims(Tools::AnimationInfo anims);
};