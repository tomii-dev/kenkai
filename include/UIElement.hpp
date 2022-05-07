#pragma once

#include <string>
#include <functional>

#include "SFML/Graphics.hpp"
#include "Game.hpp"

class UIElement {
	sf::Sprite sprite;
	sf::Texture texture;
	std::function<void()> behaviour;
public:
	std::string name;
	UIElement();
	UIElement(std::string name, std::string path, float sizeX, float sizeY);
	void DrawTo(sf::RenderWindow& window);
	void setBehaviour(std::function<void()> behaviour);
	void setPosition(sf::Vector2f pos);
	void setPosition(float x, float y);
	void Update();
};
