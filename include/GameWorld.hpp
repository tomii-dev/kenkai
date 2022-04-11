#pragma once

#include "SFML/Graphics.hpp"
#include <list>
#include "Camera.hpp"

class Entity;

class GameWorld {
	sf::RenderWindow& window;
	Camera camera = Camera(window, DEFAULT_MODE);
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