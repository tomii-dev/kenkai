#pragma once

#include "UIElement.hpp"

class Cursor : public UIElement {
	int mouseMoveFrame;
	float deg;
	sf::Vector2i lastMousePos;
	bool mouseMoved;
	bool centerMouse;
	void Setup();
public:
	Cursor();
	Cursor(float sizeX, float sizeY);
	void Update() override;
};