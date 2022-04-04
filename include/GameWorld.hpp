#pragma once

#include "SFML/Graphics.hpp"
#include <list>

class Entity;

class GameWorld {
	sf::RenderWindow& window;
	sf::Texture backgroundTex;
	sf::Sprite worldBackground;
	std::list<Entity*> entities;
public:
	GameWorld(sf::RenderWindow& _window);
	void Render();
	void RenderEntities();
	void AddEntity(Entity *entity);
	void RemoveEntity(Entity* entity);
};