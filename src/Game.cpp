#include <iostream>
#include <vector>

#include "Game.hpp"
#include "GameWorld.hpp"
#include "Control.hpp"
#include "Properties.hpp"
#include "Tools.hpp"
#include "Entity.hpp"
#include "Entities/Player.hpp"
#include "Entities/Enemy.hpp"
#include "AnimatedEntity.hpp"

#include "SFML/Graphics.hpp"

using namespace Control;

namespace Game {
	bool ready = false;
	int frame = 0;
	int totalFrame = 0;
	Player player(Tools::PlayerConfig("player"));
	sf::RenderWindow window(sf::VideoMode(800, 600), "kenkai", sf::Style::Close);
	GameWorld world(window);
	sf::Text msg;

	void RunGame() {
		window.setFramerateLimit(144);
		sf::Event e;

		Enemy bad;

		// set up player animations
		player.setAnims(Tools::GetAnimsById("player"));
		bad.setAnims(Tools::GetAnimsById("player"));

		world.AddEntity(&player);
		world.AddEntity(&bad);

		ready = true;

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
			world.WorldPhysics();
			Tools::LogicUpdate();
			world.Render();
			window.display();
			++frame;
			++totalFrame;
			if (frame == Properties::frameRate - 1) frame = 0;
		}
	}
}

int main() {

	Game::RunGame();

	return 0;
}