#include <iostream>
#include <math.h>

#include "Game.hpp"
#include "Tools.hpp"
#include "Events.hpp"
#include "UIElements/Cursor.hpp"
#include "Entities/Player.hpp"
#include "SFML/Graphics.hpp"

Cursor::Cursor(){
	Setup();
}

Cursor::Cursor(float sizeX, float sizeY) {
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	Setup();
}

void Cursor::Setup() {
	name = "cursor";
	setTexture("cursor.png");
	Events::HookTo("MouseMoved", [this]()->void { mouseMoved = true; });
	deg = 0;
}

void Cursor::Update() {
	sf::Vector2f playerCent = Game::player.getCenter();
	setPosition(playerCent + sf::Vector2f(50 * sin(deg), -(50 * cos(deg))));
	deg += 0.05;
	if (deg == 360) deg = 0;
} 