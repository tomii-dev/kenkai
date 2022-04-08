#pragma once

#include "SFML/Graphics.hpp"

class Player;
class Entity;
class GameWorld;

namespace Game {

	extern int frame;
	extern int totalFrame;
	extern Player player;
	extern GameWorld world;

	extern sf::RenderWindow window;

	void RunGame();
}
