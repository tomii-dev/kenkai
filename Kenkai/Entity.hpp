#pragma once

#include "SFML/Graphics.hpp"
#include "Game.hpp"

class Entity{
protected:
	sf::Sprite sprite;
	sf::Texture texture;
public:
	std::string name;
	sf::Vector2f position;
	bool up;
	bool down;
	bool left;
	bool right; 

	Entity();

	sf::Sprite getSprite();
	void Update();
	virtual void AnimUpdate();
	void setTexture(sf::Texture& texture);

	void DrawTo(sf::RenderWindow& window);
};