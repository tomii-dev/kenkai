#include <iostream>

#include "GameWorld.hpp"
#include "Entities/Player.hpp"
#include "Entity.hpp"
#include "Engine.hpp"
#include "AnimatedEntity.hpp"
#include "Events.hpp"

GameWorld::GameWorld(sf::RenderWindow& _window) : window(_window) {
	backgroundTex.loadFromFile("assets/textures/environment/background.png");
	groundHeight = 500;
	Events::RegisterEvents();
}

void GameWorld::WorldPhysics() {
	std::list<Entity*>::iterator it;
	for (it = entities.begin(); it != entities.end(); it++) {
		if ((*it)->jumping) continue;
		if ((*it)->getY() >= groundHeight) {
			(*it)->inAir = false;
			continue;
		}
		else (*it)->inAir = true;
		Engine::ApplyGravity(*it);
	}
}

void GameWorld::Render() {
	sf::Sprite worldBackground;
	worldBackground.setTexture(backgroundTex);
	window.draw(worldBackground);

	RenderEntities();
}

void GameWorld::RenderEntities() {
	std::list<Entity*>::iterator it;
	for (it = entities.begin(); it != entities.end(); it++) {
		(*it)->Update();
		(*it)->DrawTo(window);
	}
}

void GameWorld::AddEntity(Entity *entity) {
	entities.push_back(entity);
}

void GameWorld::RemoveEntity(Entity* entity) {
	entities.remove(entity);
}