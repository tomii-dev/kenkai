#pragma once

#include "SFML/Graphics.hpp"

class Entity {
protected:
	sf::Sprite sprite;
	sf::Texture texture;
	bool registerColl;
	int jumpSpeed;
	sf::Vector2f centerOffset;
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
	bool dead;

	Entity();
	virtual ~Entity() {}

	sf::Sprite getSprite();
	sf::Vector2f getPosition();
	void SetPosition(float x, float y);
	void Move(float x, float y);
	void Move(sf::Vector2f vec);
	void Update();
	void Destroy();
	virtual void AnimUpdate();
	virtual void OnPlayerCollision();
	virtual void UniqueUpdate();
	void setTexture(sf::Texture& texture);
	float getX();
	float getY();
	sf::Vector2f getCenter();
	bool inXRangeOf(Entity entity, float offset);

	void DrawTo(sf::RenderWindow& window);
};