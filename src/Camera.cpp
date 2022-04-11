#include <iostream>
#include "Camera.hpp"

Camera::Camera(sf::RenderWindow& _window, int _mode) : window(_window), mode(_mode) {
	setCenter(window.getSize().x / 2, window.getSize().y / 2);
	setSize(window.getSize().x, window.getSize().y);
	viewRange = getSize();
}

void Camera::Update(sf::Vector2f targetPos, sf::Vector2f offset) {
	switch (mode) {
	case DEFAULT_MODE:
		std::cout << targetPos.x << ", " << targetPos.y << std::endl;
		if (targetPos.x >= (viewRange.x * 0.8)) {
			setCenter(getCenter().x + 2, getCenter().y);
			viewRange.x += 2;
		}
		if (targetPos.x <= (viewRange.x * 0.8)) {
			setCenter(getCenter().x - 2, getCenter().y);
			viewRange.x -= 2;
		}
		break;
	case SLOW_FOLLOW_MODE:
		break;
	case DIRECT_FOLLOW_MODE:
		setCenter(targetPos + offset);
		break;
	}
	window.setView(*this);
}