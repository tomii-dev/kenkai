#include <iostream>

#include "UIElement.hpp"
#include "Tools.hpp"

UIElement::UIElement() {
	sizeX, sizeY = 0;
}

void UIElement::DrawTo(sf::RenderWindow& window) {
	window.draw(sprite);
}

void UIElement::setPosition(sf::Vector2f pos) {
	sprite.setPosition(pos);
}

void UIElement::setTexture(std::string path) {
	texture.loadFromFile(UI_ELEMENTS + path);
	texture.setSmooth(true);
	sprite.setTexture(texture);
	if (!sizeX) return;
	sprite.setScale(
		sizeX / texture.getSize().x,
		sizeY / texture.getSize().y
	);
}

void UIElement::setPosition(float x, float y) {
	sprite.setPosition(sf::Vector2f(x, y));
}

void UIElement::Update() {}