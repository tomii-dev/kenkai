#pragma once

#include "SFML/Graphics.hpp"
#include <list>
#include <vector>
#include "Camera.hpp"

class Entity;

class GameWorld {
	sf::RenderWindow& window;
	sf::Texture backgroundTex;
	sf::Texture groundTex;
	sf::Sprite ground;
	std::list<Entity*> entities;
	std::vector<Entity*> purgeEntities;
	float groundHeight;
public:
	GameWorld(sf::RenderWindow& _window);
	void WorldPhysics();
	void Render();
	void RenderEntities();
	void PurgeEnemies();
	void AddEntity(Entity *entity);
	void RemoveEntity(Entity *entity);
};