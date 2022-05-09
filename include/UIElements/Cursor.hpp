#pragma once

#include "UIElement.hpp"

class Cursor : public UIElement {
	float deg;
	sf::Vector2f lastMousePos;
	bool mouseMoved;
	void Setup();
public:
	Cursor();
	Cursor(float sizeX, float sizeY);
	void Update() override;
};