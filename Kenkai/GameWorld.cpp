#include <iostream>

#include "GameWorld.hpp"
#include "Entity.hpp"
#include "AnimatedEntity.hpp"

GameWorld::GameWorld(sf::RenderWindow& _window) : window(_window) {}

void GameWorld::Render() {
	RenderEntities();
}

void GameWorld::RenderEntities() {
	for (Entity& entity : entities) {
		entity.Update();
		entity.DrawTo(window);
	}
}

void GameWorld::AddEntity(Entity entity) {
	entities.push_back(entity);
}