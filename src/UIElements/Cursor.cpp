#include <iostream>

#include "Game.hpp"
#include "Tools.hpp"
#include "UIElements/Cursor.hpp"
#include "Entities/Player.hpp"
#include "SFML/Graphics.hpp"

Cursor::Cursor(){
	name = "cursor";
	setTexture("cursor.png");
}

Cursor::Cursor(float sizeX, float sizeY) {
	name = "cursor";
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	setTexture("cursor.png");
}

void Cursor::Update() {
	sprite.setPosition(Game::player.getPosition() + sf::Vector2f(50, 30));
} 