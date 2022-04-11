#pragma once

#include "SFML/Graphics.hpp"

class Camera : public sf::View {
	sf::RenderWindow& window;
public:
	void Update(sf::Vector2f targetPos, sf::Vector2f offset);
	Camera(sf::RenderWindow& _window);
};