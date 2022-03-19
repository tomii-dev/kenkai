#pragma once
#include "SFML/Graphics.hpp"
#include "AnimatedEntity.hpp"

namespace Game {

	int frame;
	AnimatedEntity player(50, 50);

	sf::RenderWindow window(sf::VideoMode(800, 600), "balls");

	void RunGame();
}