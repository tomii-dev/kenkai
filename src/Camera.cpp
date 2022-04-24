#include <iostream>
#include <cstdlib>
#include "Camera.hpp"
#include "Tools.hpp"
#include "Events.hpp"

Camera::Camera(sf::RenderWindow& _window, int _mode) : window(_window), mode(_mode) {
	setCenter(window.getSize().x / 2, window.getSize().y / 2);
	setSize(window.getSize().x, window.getSize().y);
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
	sf::Vector2f viewStart = getCenter() - (getSize() / 2.f);
	switch (mode) {
	case DEFAULT_MODE:
		if (targetPos.x >= 0.75 * getSize().x + viewStart.x) {
			setCenter(getCenter().x + 2, getCenter().y);
		}
		if (targetPos.x <= 0.20 * getSize().x + viewStart.x) {
			setCenter(getCenter().x - 2, getCenter().y);
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