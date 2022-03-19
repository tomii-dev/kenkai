#include <iostream>

#include "Game.hpp"
#include "Control.hpp"
#include "Properties.hpp"

#include "SFML/Graphics.hpp"

using namespace Game;
using namespace Control;

void Game::RunGame() {
	window.setFramerateLimit(144);
	sf::Event e;

	sf::Texture texture1;
	texture1.loadFromFile("assets/link.png");
	sf::Texture texture2;
	texture2.loadFromFile("assets/link2.png");
	sf::Texture texture3;
	texture3.loadFromFile("assets/link3.png");
	sf::Texture playerTextures[10];
	playerTextures[0] = texture1;
	playerTextures[1] = texture2;
	playerTextures[2] = texture3;
	player.setTextures(playerTextures);

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