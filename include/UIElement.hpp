#pragma once

#include <string>
#include <functional>

#include "SFML/Graphics.hpp"

class UIElement {
protected:
	sf::Sprite sprite;
	sf::Texture texture;
	float m_sizeX;
	float m_sizeY;
	bool visible;
public:
	std::string name;
	UIElement();
	UIElement(float sizeX, float sizeY);
	sf::Vector2f getPosition();
	sf::Vector2f getCenter();
	void DrawTo(sf::RenderWindow& window);
	void setTexture(std::string path);
	void setPosition(sf::Vector2f pos);
	void setPosition(float x, float y);
	virtual void Update();
};
