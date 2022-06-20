#include <iostream>

#include "UIElement.hpp"
#include "Tools.hpp"

UIElement::UIElement(float sizeX, float sizeY, sf::Vector2f pos) 
	: visible(true),
	m_sizeX  	(sizeX),
	m_sizeY  	(sizeY),
	m_position	(pos)
{}

void UIElement::Setup(){
	setPosition(m_position);
	setTexture(name + ".png");
}

sf::Vector2f UIElement::getPosition(){
	return sprite.getPosition();
}

ElementType UIElement::getType(){
	return m_type;
}

sf::Vector2f UIElement::getCenter() {
	return sf::Vector2f(getPosition().x + m_sizeX / 2, getPosition().y + m_sizeY/ 2);
}

void UIElement::DrawTo(sf::RenderWindow* window) {
	if (!visible) return;
	window->draw(sprite);
}

void UIElement::setPosition(sf::Vector2f pos) {
	sf::Vector2f newPos(pos.x - (m_sizeX/ 2), pos.y - (m_sizeY / 2));
	sprite.setPosition(newPos);
}

void UIElement::setTexture(std::string path) {
	texture.loadFromFile(UI_ELEMENTS + path);
	texture.setSmooth(true);
	sprite.setTexture(texture);
	if (!m_sizeX) return;
	sprite.setScale(
		m_sizeX / texture.getSize().x,
		m_sizeY / texture.getSize().y
	);
	m_sizeX = sprite.getTexture()->getSize().x * sprite.getScale().x;
	m_sizeY = sprite.getTexture()->getSize().y * sprite.getScale().y;
}

void UIElement::setPosition(float x, float y) {
	sprite.setPosition(sf::Vector2f(x, y));
}

void UIElement::Update() {}