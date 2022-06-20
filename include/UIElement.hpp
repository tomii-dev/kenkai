#pragma once

#include <string>
#include <functional>

#include "SFML/Graphics.hpp"

#define VEC0 sf::Vector2f()

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
	UIElement(float sizeX=0, float sizeY=0, sf::Vector2f position=VEC0);
	sf::Vector2f getPosition();
	sf::Vector2f getCenter();
	virtual void DrawTo(sf::RenderWindow* window);
	void setTexture(std::string path);
	void setPosition(sf::Vector2f pos);
	void setPosition(float x, float y);
	virtual void Update();
	ElementType getType();
};
