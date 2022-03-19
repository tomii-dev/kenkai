#pragma once
#include "SFML/Graphics.hpp"

class Entity{
protected:
	sf::Sprite sprite;
	sf::Texture texture;
public:
	bool up;
	bool down;
	bool left;
	bool right; 

	Entity();

	void Update();
	virtual void AnimUpdate();

	void DrawTo(sf::RenderWindow& window);
};