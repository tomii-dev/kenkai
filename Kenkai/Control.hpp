#include <iostream>

#include "Game.hpp"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Player.hpp"

namespace Control {

	void HandleControl(sf::Keyboard::Key key, bool pressed) {
		switch (key) {
			case sf::Keyboard::W:
				Game::player.up = pressed;
				break;
			case sf::Keyboard::S:
				Game::player.down = pressed;
				break;
			case sf::Keyboard::A:
				Game::player.left = pressed;
				break;
			case sf::Keyboard::D:
				Game::player.right = pressed;
				break;
		}
	}
}