#include <iostream>
#include <math.h>

#include "Game.hpp"
#include "Properties.hpp"
#include "Tools.hpp"
#include "Events.hpp"
#include "GameWorld.hpp"
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
	deg = 0;
	mouseMoveFrame = 0;
	mouseMoved = false;
	centerMouse = true;
	Events::HookTo("MouseMoved", [this]() ->void { mouseMoved = true; });
}

void Cursor::Update() {
	sf::Vector2f playerCent = Game::player.getCenter();
	sf::Vector2f mousePos = Tools::getMousePosition();
	if (mouseMoved) {
		mouseMoveFrame = Game::totalFrame;
		sf::Vector2f diff = playerCent - mousePos;
		deg = atan2(diff.x, diff.y);
		visible = true;
		centerMouse = false;
	}
	if (Game::totalFrame == mouseMoveFrame + Tools::getFrames(500)) centerMouse = true;
	if (centerMouse) visible = false;
	else setPosition(playerCent - sf::Vector2f(50 * sin(deg), (50 * cos(deg))));
	mouseMoved = false;
} 