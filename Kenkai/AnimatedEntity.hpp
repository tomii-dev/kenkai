#include "Entity.hpp"
#include "Tools.hpp"

#include "SFML/Graphics.hpp"

class AnimatedEntity : public Entity {
	Tools::AnimationInfo anims;
	void AnimUpdate() override;
	void ResetValues();
	int frame;
	int frameGap;
	int animFrame;
	int nextAnimFrame;
public:
	AnimatedEntity(float x, float y);
	void setAnims(Tools::AnimationInfo anims);
};