#include <iostream>
#include <random>

#include "Entity.hpp"
#include "Collision.hpp"
#include "Game.hpp"
#include "Events.hpp"
#include "Entities/Player.hpp"

Entity::Entity() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 999999);
	id = std::to_string(dist(gen));
	velocity = sf::Vector2f();
	left = false;
	right = false;
	jumping = false;
	canJump = true;
	inAir = false;
	registerColl = true;
	dead = false;
	Events::HookTo("GameReady", [this]() { Setup(); });
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
void Entity::OnPlayerCollision() { registerColl = false; }
void Entity::Die(){}

bool Entity::inXRangeOf(Entity entity, float offset) {
	float entX = entity.getX();
	return getX() >= (entX - offset) && getX() <= (entX + offset);
}

void Entity::SetPosition(float x, float y) {
	sprite.setPosition(sf::Vector2f(x, y));
}

void Entity::Setup() {
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