#pragma once

#include "SFML/Graphics.hpp"

#define DEFAULT_MODE 0
#define SLOW_FOLLOW_MODE 1
#define DIRECT_FOLLOW_MODE 2
#define OVERRIDE_MODE 3

class Camera : public sf::View {
	sf::RenderWindow& window;
	sf::Vector2f viewRange;
	int mode;
public:
	void Update(sf::Vector2f targetPos, sf::Vector2f offset);
	void PanTo(sf::Vector2f pos, int ms, bool stay, int returnAfter);
	Camera(sf::RenderWindow& _window, int mode);
};