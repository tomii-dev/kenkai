#pragma once

#include <map>
#include "Entity.hpp"
#include "Tools.hpp"

#include "SFML/Graphics.hpp"

class AnimatedEntity : public Entity {
	std::map<std::string, Tools::Animation> anims;
	void AnimUpdate() override;
	void ResetValues();
	void setFrameGap(std::string id);
	int frame;
	int frameGap;
	int animFrame;
	int nextAnimFrame;
	std::string lastAnimId;
protected:
	void PlayAnim(std::string id);
	void Setup() override;
public:
	AnimatedEntity();
	void setAnims(std::map<std::string, Tools::Animation> anims);
};