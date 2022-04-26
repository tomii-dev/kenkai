#pragma once

#include "Entity.hpp"
#include <map>
#include "Tools.hpp"

#include "SFML/Graphics.hpp"

class AnimatedEntity : public Entity {
	std::map<std::string, Tools::Animation> anims;
	void AnimUpdate() override;
	void ResetValues();
	int frameGap;
	int animFrame;
	int nextAnimFrame;
protected:
	void PlayAnim(std::string id);
	void Setup() override;
public:
	AnimatedEntity();
	void setAnims(std::map<std::string, Tools::Animation> anims);
};