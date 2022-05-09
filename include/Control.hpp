#include <iostream>

#include "Game.hpp"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Entities/Player.hpp"

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
			case sf::Keyboard::Space:
				if (pressed) Game::player.Jump();
				break;
			case sf::Keyboard::LShift:
				if (pressed) Events::Fire("ShiftPressed");
				else Events::Fire("ShiftReleased");
				break;
			case sf::Keyboard::Escape:
				if (pressed) Events::Fire("EscPressed");
		}
	}
}