#pragma once

#include "SFML/Graphics.hpp"

class Player;
class Entity;

namespace Game {

	extern int frame;
	extern Player player;

	extern sf::RenderWindow window;

	void RunGame();
}
