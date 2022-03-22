#pragma once
#include "SFML/Graphics.hpp"
#include "AnimatedEntity.hpp"

namespace Game {

	int frame;
	AnimatedEntity player(1200, 1200);

	sf::RenderWindow window(sf::VideoMode(800, 600), "balls");

	void RunGame();
}