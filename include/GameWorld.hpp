#pragma once

#include "SFML/Graphics.hpp"
#include <list>

class Entity;

class GameWorld {
	sf::RenderWindow& window;
	sf::Texture backgroundTex;
	sf::Texture groundTex;
	sf::Sprite ground;
	sf::Sprite worldBackground;
	std::list<Entity*> entities;
	float groundHeight;
public:
	GameWorld(sf::RenderWindow& _window);
	void WorldPhysics();
	void Render();
	void RenderEntities();
	void AddEntity(Entity *entity);
	void RemoveEntity(Entity *entity);
};