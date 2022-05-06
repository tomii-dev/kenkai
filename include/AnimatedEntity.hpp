#pragma once

#include <map>
#include "Entity.hpp"
#include "Tools.hpp"

#include "SFML/Graphics.hpp"

class AnimatedEntity : public Entity {
	std::map<std::string, Tools::Animation> anims;
	std::string animId;
	std::string overrideAnimId;
	int frame;
	int frameGap;
	int maxFrame;
	int animFrame;
	int nextAnimFrame;
	bool override;
	std::string lastAnimId;
	void ResetValues();
	void SetValues(std::string id);
	void PlayAnim(std::string id);
protected:
	void AnimUpdate() override;
	void setAnim(std::string id, bool playFull=false);
	void Setup() override;
public:
	AnimatedEntity();
	void setAnims(std::map<std::string, Tools::Animation> anims);
};