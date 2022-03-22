#include <iostream>
#include <vector>

#include "Game.hpp"
#include "Control.hpp"
#include "Properties.hpp"
#include "Tools.hpp"

#include "SFML/Graphics.hpp"

using namespace Game;
using namespace Control;

void Game::RunGame() {
	window.setFramerateLimit(144);
	sf::Event e;

	// set up player animations
	player.setAnims(Tools::GetAnimsById("player"));

	// main loop
	while (window.isOpen()) {
		while (window.pollEvent(e)) {
			switch (e.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				HandleControl(e.key.code, true);
				break;
			case sf::Event::KeyReleased:
				HandleControl(e.key.code, false);
				break;
			}
		}
		window.clear(sf::Color::Blue);
		player.Update();
		player.DrawTo(window);
		window.display();
		frame++;
		if (frame == Properties::frameRate) frame = 0;
	}
}

int main() {

	Game::RunGame();

	return 0;
}