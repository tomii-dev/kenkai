#include <iostream>

#include "Game.hpp"
#include <iostream>
#include "SFML/Graphics.hpp"

namespace Control {

	void HandleControl(sf::Keyboard::Key key, bool pressed) {
		if (pressed) {
			switch (key) {
			case sf::Keyboard::W:
				Game::player.up = true;
				break;
			case sf::Keyboard::S:
				Game::player.down = true;
				break;
			case sf::Keyboard::A:
				Game::player.left = true;
				break;
			case sf::Keyboard::D:
				Game::player.right = true;
				break;
			}
		}
		else {
			Game::player.up = false;
			Game::player.down = false;
			Game::player.left = false;
			Game::player.right = false;
		}
	}
}