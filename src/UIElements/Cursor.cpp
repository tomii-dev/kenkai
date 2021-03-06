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

Cursor::Cursor() {
	Setup();
}

Cursor::Cursor(float sizeX, float sizeY)
	: UIElement(sizeX, sizeY)
{
	Setup();
}

void Cursor::Setup() {
	name = "cursor";
	m_type = ElementType::Cursor;
	deg = 0;
	mouseMoveFrame = 0;
	mouseMoved = false;
	centerMouse = true;
	visible = false;
	Events::HookTo(MouseMoved, [this]() ->void { mouseMoved = true; });
	UIElement::Setup();
}

void Cursor::Update() {
	switch (Game::getInstance().getState()) {
	case MENU:
		visible = true;
		setPosition(Tools::getMousePosition());
		break;
	case PLAYING:
		int totalFrame = Game::getInstance().getTotalFrame();
		sf::Vector2f playerCent = Game::getInstance().player->getCenter();
		sf::Vector2f mousePos = Tools::getMousePosition();
		if (mouseMoved) {
			mouseMoveFrame = totalFrame;
			sf::Vector2f diff = playerCent - mousePos;
			deg = atan2(diff.x, diff.y);
			visible = true;
		}
		if (totalFrame == mouseMoveFrame + Tools::getFrames(500))
			visible = false;
		else setPosition(playerCent - sf::Vector2f(50 * sin(deg), (50 * cos(deg))));
		mouseMoved = false;
		break;
	}
} 