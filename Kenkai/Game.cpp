#include <iostream>
#include <vector>

#include "Game.hpp"
#include "GameWorld.hpp"
#include "Control.hpp"
#include "Properties.hpp"
#include "Tools.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "AnimatedEntity.hpp"

#include "SFML/Graphics.hpp"

using namespace Control;

namespace Game {
	int frame = 0;
	Player player(Tools::PlayerConfig("balls"));
	Entity link;
	sf::RenderWindow window(sf::VideoMode(800, 600), "balls", sf::Style::Close);

	void RunGame() {

		GameWorld world(window);

		sf::RectangleShape background(sf::Vector2f(800, 600));
		sf::Texture backgroundTexture;
		backgroundTexture.loadFromFile("assets/textures/environment/background.png");
		background.setTexture(&backgroundTexture);

		window.setFramerateLimit(144);
		sf::Event e;

		sf::Texture linkTexture;
		linkTexture.loadFromFile("assets/animations/1.png");

		link.setTexture(linkTexture);

		// set up player animations
		player.setAnims(Tools::GetAnimsById("player"));
		
		world.AddEntity(player);
		world.AddEntity(link);

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