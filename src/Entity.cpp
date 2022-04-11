#include <iostream>

#include "Entity.hpp"
#include "Collision.hpp"
#include "Game.hpp"
#include "Entities/Player.hpp"

Entity::Entity() {
	velocity = sf::Vector2f();
	left = false;
	right = false;
	jumping = false;
	canJump = true;
	inAir = false;
	registerColl = true;
}

sf::Sprite Entity::getSprite() {
	return sprite;
}

sf::Vector2f Entity::getPosition() {
	return sprite.getPosition();
}

void Entity::setTexture(sf::Texture& texture) {
	sprite.setTexture(texture);
}

void Entity::AnimUpdate() {}
void Entity::UniqueUpdate(){}
void Entity::OnPlayerCollision() {}
void Entity::Die(){}

void Entity::SetPosition(float x, float y) {
	sprite.setPosition(sf::Vector2f(x, y));
}

void Entity::Move(float x, float y) { sprite.move(x, y); velocity = sf::Vector2f(x, y); }
void Entity::Move(sf::Vector2f vec) { sprite.move(vec); velocity = vec; }

float Entity::getX() {
	return sprite.getPosition().x;
}

float Entity::getY() {
	return sprite.getPosition().y;
}

void Entity::Update() {

	if (!Game::ready) return;

	sf::Vector2f movement;

	if (left) movement.x -= moveSpeed;
	if (right) movement.x += moveSpeed;

	velocity = movement;

	sprite.move(movement);
	UniqueUpdate();
	AnimUpdate();

	if (health <= 0) Die();
	if (name == "player") return;

	if (!registerColl) return;

	if (Collision::PixelPerfectTest(sprite, Game::player.getSprite())) OnPlayerCollision();
}

void Entity::DrawTo(sf::RenderWindow& window) {
	window.draw(sprite);
}