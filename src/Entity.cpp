#include <iostream>

#include "Entity.hpp"
#include "Collision.hpp"
#include "Game.hpp"
#include "Entities/Player.hpp"

Entity::Entity() {
	movement = sf::Vector2f();
	left = false;
	right = false;
	jumping = false;
	canJump = true;
	inAir = false;
	weight = 30;
}

sf::Sprite Entity::getSprite() {
	return sprite;
}

void Entity::setTexture(sf::Texture& texture) {
	sprite.setTexture(texture);
}

void Entity::AnimUpdate() {}
void Entity::OnPlayerCollision() {}

void Entity::Move(float x, float y) { movement = sf::Vector2f(x, y); }

float Entity::getX() {
	return sprite.getPosition().x;
}

float Entity::getY() {
	return sprite.getPosition().y;
}

void Entity::Update() {

	if (!inAir) movement = sf::Vector2f();

	if (left) movement.x -= moveSpeed;
	if (right) movement.x += moveSpeed;

	sprite.move(movement);
	AnimUpdate();

	std::cout << name << " health: " << health << std::endl;
	if (name == "player") return;

	if (Collision::PixelPerfectTest(sprite, Game::player.getSprite())) OnPlayerCollision();
}

void Entity::DrawTo(sf::RenderWindow& window) {
	window.draw(sprite);
}