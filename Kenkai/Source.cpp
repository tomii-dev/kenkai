#include <iostream>

#include "SFML/Graphics.hpp"

int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "balls");
	sf::Event e;

	// main loop
	while (window.isOpen()) {
		while (window.pollEvent(e)) {
			switch (e.type) {
				case sf::Event::Closed:
					window.close();
					break;
			}
		}

		window.clear(sf::Color::Blue);
		window.display();
	}

	return 0;
}