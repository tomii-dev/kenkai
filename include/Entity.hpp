#pragma once

#include "SFML/Graphics.hpp"
#include "Game.hpp"

class Entity {
protected:
	sf::Sprite sprite;
	sf::Texture texture;
	bool registerColl;
	int jumpSpeed;
	virtual void Die();
	virtual void Setup();
public:
	std::string name;
	std::string id;
	sf::Vector2f velocity;
	int weight;
	bool up;
	bool down;
	bool left;
	bool right;
	bool canJump;
	bool jumping;
	bool inAir;
	int moveSpeed;
	int health;

	Entity();
	virtual ~Entity() {}

	sf::Sprite getSprite();
	sf::Vector2f getPosition();
	void SetPosition(float x, float y);
	void Move(float x, float y);
	void Move(sf::Vector2f vec);
	void Update();
	virtual void AnimUpdate();
	virtual void OnPlayerCollision();
	virtual void UniqueUpdate();
	void setTexture(sf::Texture& texture);
	float getX();
	float getY();

	void DrawTo(sf::RenderWindow& window);
};