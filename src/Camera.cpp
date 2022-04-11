#include <iostream>
#include "Camera.hpp"

Camera::Camera(sf::RenderWindow& _window) : window(_window) {
	setCenter(400, 300);
	setSize(800, 600);
}

void Camera::Update(sf::Vector2f targetPos, sf::Vector2f offset) {
	setCenter(getCenter().x + 0.01f, getCenter().y + 0.01f);
	window.setView(*this);
}