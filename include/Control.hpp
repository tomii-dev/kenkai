#include <iostream>

#include "Game.hpp"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Entities/Player.hpp"

namespace Control {

	void HandleControl(sf::Keyboard::Key key, bool pressed) {
		Player& player = *Game::getInstance().player;
		switch (key) {
			case sf::Keyboard::W:
				player.up = pressed;
				break;
			case sf::Keyboard::S:
				player.down = pressed;
				break;
			case sf::Keyboard::A:
				player.left = pressed;
				break;
			case sf::Keyboard::D:
				player.right = pressed;
				break;
			case sf::Keyboard::Space:
				if (pressed) player.Jump();
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