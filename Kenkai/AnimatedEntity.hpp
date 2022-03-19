#include "Entity.hpp"

#include "SFML/Graphics.hpp"

class AnimatedEntity : public Entity {
	sf::Texture frames[144];
	void AnimUpdate() override;
	void ResetValues();
	int frameCount;
	int frame;
	int frameGap;
	int animFrame;
	int nextAnimFrame;
public:
	AnimatedEntity(float x, float y);
	void setTextures(sf::Texture* textures);
};