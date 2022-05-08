#pragma once

#include "UIElement.hpp"

class Cursor : public UIElement {
public:
	Cursor();
	Cursor(float sizeX, float sizeY);
	void Update() override;
};