#include <iostream>

#include "Entity.hpp"
#include "Collision.hpp"
#include "Game.hpp"
#include "Entities/Player.hpp"

Entity::Entity() {
	up = false;
	down = false;
	left = false;
	right = false;
}

sf::Sprite Entity::getSprite() {
	return sprite;
}

void Entity::setTexture(sf::Texture& texture) {
	sprite.setTexture(texture);
}

void Entity::AnimUpdate() {}
void Entity::OnPlayerCollision() {}

void Entity::Move(sf::Vector2f vec) { sprite.move(vec); }

void Entity::Update() {
	sf::Vector2f movement;

	if (up) movement.y -= 1.0;
	if (down) movement.y += 1.0;
	if (left) movement.x -= 1.0;
	if (right) movement.x += 1.0;

	m_movement = movement;

	sprite.move(movement);
	AnimUpdate();

	if (name == "player") return;

	if (Collision::PixelPerfectTest(sprite, Game::player.getSprite())) {
		std::cout << "BRO THEY TOUCHIN" << std::endl;
	}
}

void Entity::DrawTo(sf::RenderWindow& window) {
	window.draw(sprite);
}