#pragma once

#include <string>
#include <functional>

#include "SFML/Graphics.hpp"

enum class ElementType{
	Button,
	Cursor
};

class UIElement {
protected:
	std::string name;
	ElementType m_type;
	sf::Sprite sprite;
	sf::Texture texture;
	float m_sizeX;
	float m_sizeY;
	sf::Vector2f m_position;
	bool visible;
	virtual void Setup();
	friend class MenuBuilder;
public:
	UIElement();
	UIElement(float sizeX, float sizeY);
	sf::Vector2f getPosition();
	sf::Vector2f getCenter();
	void DrawTo(sf::RenderWindow* window);
	void setTexture(std::string path);
	void setPosition(sf::Vector2f pos);
	void setPosition(float x, float y);
	virtual void Update();
	ElementType getType();
};
