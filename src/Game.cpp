#include <iostream>
#include <vector>

#include "Setup.hpp"
#include "Game.hpp"
#include "GameWorld.hpp"
#include "Control.hpp"
#include "Properties.hpp"
#include "Tools.hpp"
#include "Events.hpp"
#include "Entity.hpp"
#include "Entities/Player.hpp"
#include "Entities/Enemy.hpp"
#include "AnimatedEntity.hpp"

#include "SFML/Graphics.hpp"

using namespace Control;

namespace Game {
	Setup setup;
	bool ready = false;
	int frame = 0;
	int totalFrame = 0;
	Player player(Tools::PlayerConfig("player"));
	sf::RenderWindow window(sf::VideoMode(800, 600), "kenkai", sf::Style::Close);
	GameWorld world(window);
	Camera camera = Camera(window, DEFAULT_MODE);
	sf::Text msg;

	void RunGame() {

		window.setFramerateLimit(144);

		sf::View view(sf::FloatRect(0, 0, 800.f, 600.f));
		window.setView(view);

		sf::Event e;

		for (int i = 0; i < 20; i++) {
			Enemy *bad = new Enemy();
			bad->SetPosition(i * 30, 200);
			world.AddEntity(bad);
		}

		world.AddEntity(&player);

		ready = true;
		Events::Fire("GameReady");

		// main loop
		while (window.isOpen()) {
			while (window.pollEvent(e)) {
				switch (e.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					HandleControl(e.key.code, true);
					Events::Fire("PlayerMoved");
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
			camera.Update(player.getPosition(), sf::Vector2f(0, -200));
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