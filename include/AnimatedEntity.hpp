#pragma once

#include <map>
#include "Entity.hpp"
#include "Tools.hpp"

#include "SFML/Graphics.hpp"

class AnimatedEntity : public Entity {
	std::map<std::string, Tools::Animation> anims;
	std::string animId;
	int frame;
	int frameGap;
	int maxFrame;
	int animFrame;
	int nextAnimFrame;
	int override;
	int overrideAnimCount;
	std::string lastAnimId;
	void AnimUpdate() override;
	void ResetValues();
	void SetValues(std::string id);
	void PlayAnim(std::string id);
protected:
	void setAnim(std::string id);
	void Setup() override;
public:
	AnimatedEntity();
	void setAnims(std::map<std::string, Tools::Animation> anims);
};