#include <iostream>
#include <vector>

#include "Game.hpp"
#include "GameWorld.hpp"
#include "Control.hpp"
#include "Properties.hpp"
#include "Tools.hpp"
#include "Entity.hpp"
#include "Entities/Player.hpp"
#include "AnimatedEntity.hpp"

#include "SFML/Graphics.hpp"

using namespace Control;

namespace Game {
	int frame = 0;
	Player player(Tools::PlayerConfig("balls"));
	sf::RenderWindow window(sf::VideoMode(800, 600), "balls", sf::Style::Close);

	void RunGame() {

		GameWorld world(window);

		window.setFramerateLimit(144);
		sf::Event e;

		// set up player animations
		player.setAnims(Tools::GetAnimsById("player"));
		
		world.AddEntity(&player);

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
			world.Render();
			window.display();
		}
	}
}

int main() {

	Game::RunGame();

	return 0;
}