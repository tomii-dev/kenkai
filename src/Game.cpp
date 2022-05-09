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
#include "UIElements/Cursor.hpp"

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
	Cursor cursor(15, 15);
	bool cursorVisible;
	bool cursorGrabbed;

	void RunGame() {

		window.setFramerateLimit(144);
		window.setMouseCursorVisible(false);
		cursorVisible = false;
		window.setMouseCursorGrabbed(true);
		cursorGrabbed = true;
		Events::HookTo("EscPressed", []()->void {
			window.setMouseCursorVisible(!cursorVisible);
			cursorVisible = !cursorVisible;
			window.setMouseCursorGrabbed(!cursorGrabbed);
			cursorGrabbed = !cursorGrabbed;
		});

		sf::Event e;

		world.AddEntity(&player);
		world.AddUIElement(&cursor);

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
				case sf::Event::MouseButtonPressed:
					if(e.mouseButton.button == sf::Mouse::Left) 
						Events::Fire("MousePressed");
					break;
				case sf::Event::MouseMoved:
					Events::Fire("MouseMoved");
					break;
				}
			}
			window.clear(sf::Color::Blue);
			world.WorldPhysics();
			Tools::LogicUpdate();
			world.Render();
			camera.Update(player.getPosition(), sf::Vector2f(0, -200), player.moveSpeed);
			window.display();
			++frame;
			++totalFrame;
			if (frame == Properties::frameRate - 1) {
				//Enemy* bad = new Enemy();
				//world.AddEntity(bad);
				frame = 0;
			}
		}
	}
}

int main() {

	Game::RunGame();

	return 0;
}