#include <iostream>

#include "Entity.hpp"

Entity::Entity() {
	if (!texture.loadFromFile("assets/link.png")) 
		std::cout << "failed to load sprite" << std::endl;
	sprite.setTexture(texture);
	up = false;
	down = false;
	left = false;
	right = false;
}

void Entity::AnimUpdate() {
	;
}

void Entity::Update() {
	sf::Vector2f movement;

	if (up) movement.y -= 1.0;
	if (down) movement.y += 1.0;
	if (left) movement.x -= 1.0;
	if (right) movement.x += 1.0;

	sprite.move(movement);
	AnimUpdate();
}

void Entity::DrawTo(sf::RenderWindow& window) {
	window.draw(sprite);
}