#include <iostream>
#include <cstdlib>
#include "Camera.hpp"
#include "Tools.hpp"

Camera::Camera(sf::RenderWindow& _window, int _mode) : window(_window), mode(_mode) {
	setCenter(window.getSize().x / 2, window.getSize().y / 2);
	setSize(window.getSize().x, window.getSize().y);
	viewRange = getSize();
}

void Camera::PanTo(sf::Vector2f pos, int ms, bool stay, int returnAfter) {
	int orgMode = mode;
	mode = OVERRIDE_MODE;
	sf::Vector2f dist = pos - getCenter();
	int incX = dist.x / Tools::getFrames(ms);
	int incY = dist.y / Tools::getFrames(ms);
	std::function<void()> endFunc;
	if (!stay) endFunc = [this, orgMode, returnAfter]()->void {
		Tools::WaitAndExec(returnAfter, [this, orgMode]()->void {mode = orgMode; }, "camera");
	};
	Tools::ExecuteFor(ms, [this, incX, incY]()->void {
		setCenter(getCenter().x + incX, getCenter().y + incY);
		}, endFunc, "camera");
}

void Camera::Update(sf::Vector2f targetPos, sf::Vector2f offset) {
	switch (mode) {
	case DEFAULT_MODE:
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
	case OVERRIDE_MODE:
		break;
	}
	window.setView(*this);
}