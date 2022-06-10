#pragma once

#include "UIElement.hpp"

class Cursor : public UIElement {
	int mouseMoveFrame;
	float deg;
	bool mouseMoved;
	bool centerMouse;
	void Setup() override;
public:
	Cursor();
	Cursor(float sizeX, float sizeY);
	void Update() override;
};