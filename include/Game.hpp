#pragma once

#include "SFML/Graphics.hpp"
#include "Camera.hpp"

class Player;
class Entity;
class GameWorld;
class Cursor;

namespace Game {
	extern bool ready;
	extern int frame;
	extern int totalFrame;
	extern Player player;
	extern GameWorld world;
	extern sf::Text msg;
	extern Cursor cursor;

	extern sf::RenderWindow window;

	void RunGame();
}
