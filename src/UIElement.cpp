#include <iostream>

#include "UIElement.hpp"
#include "Tools.hpp"

UIElement::UIElement(std::string name, std::string path, float sizeX, float sizeY) 
	: name(name){
	sf::Texture tex;
	tex.loadFromFile(UI_ELEMENTS + path);
	texture = tex;
	sprite.setTexture(texture);
	sprite.setScale(
		sizeX / texture.getSize().x,
		sizeY / texture.getSize().y
	);
}

UIElement::UIElement(){}

void UIElement::DrawTo(sf::RenderWindow& window) {
	window.draw(sprite);
}

void UIElement::setBehaviour(std::function<void()> behaviour) {
	this->behaviour = behaviour;
}

void UIElement::setPosition(sf::Vector2f pos) {
	sprite.setPosition(pos);
}

void UIElement::setPosition(float x, float y) {
	sprite.setPosition(sf::Vector2f(x, y));
}

void UIElement::Update() {
	if (behaviour == nullptr) return;
	behaviour();
}