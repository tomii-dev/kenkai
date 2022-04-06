#pragma once

#include "SFML/Graphics.hpp"
#include "Game.hpp"

class Entity {
protected:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f movement;
public:
	std::string name;
	sf::Vector2f position;
	int weight;
	bool up;
	bool down;
	bool left;
	bool right;

	Entity();
	virtual ~Entity() {}

	sf::Sprite getSprite();
	void Move(sf::Vector2f vec);
	void Update();
	virtual void AnimUpdate();
	virtual void OnPlayerCollision();
	void setTexture(sf::Texture& texture);

	void DrawTo(sf::RenderWindow& window);
};