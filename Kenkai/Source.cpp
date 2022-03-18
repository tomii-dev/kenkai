#include <iostream>

#include "SFML/Graphics.hpp"

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "balls");
	window.setFramerateLimit(144);
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

		sf::RectangleShape rect{ { 220.f, 160.f } };
		rect.setFillColor(sf::Color::White);
		rect.setPosition({ 150.f, 20.f });
		rect.rotate(20.f);

		window.clear(sf::Color::Blue);
		window.draw(rect);
		window.display();
	}

	return 0;
}