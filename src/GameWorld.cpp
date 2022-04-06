#include <iostream>

#include "GameWorld.hpp"
#include "Entity.hpp"
#include "Engine.hpp"
#include "AnimatedEntity.hpp"

GameWorld::GameWorld(sf::RenderWindow& _window) : window(_window) {
	backgroundTex.loadFromFile("assets/textures/environment/background.png");
}

void GameWorld::WorldPhysics() {
	std::list<Entity*>::iterator it;
	for (it = entities.begin(); it != entities.end(); it++) {
		Engine::ApplyGravity(*it);
	}
}

void GameWorld::Render() {
	// render world background first
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