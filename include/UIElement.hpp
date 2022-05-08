#pragma once

#include <string>
#include <functional>

#include "SFML/Graphics.hpp"
#include "Game.hpp"

class UIElement {
protected:
	sf::Sprite sprite;
	sf::Texture texture;
	float sizeX;
	float sizeY;
public:
	std::string name;
	UIElement();
	UIElement(float sizeX, float sizeY);
	void DrawTo(sf::RenderWindow& window);
	void setTexture(std::string path);
	void setPosition(sf::Vector2f pos);
	void setPosition(float x, float y);
	virtual void Update();
};
