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
	window.draw(worldBackground);

	RenderEntities();
	if (purgeEntities.size()) PurgeEntities();
}

void GameWorld::RenderEntities() {
	std::list<Entity*>::iterator it;
	for (it = entities.begin(); it != entities.end(); it++) {
		(*it)->Update();
		(*it)->DrawTo(window);
	}
}

void GameWorld::PurgeEntities() {
	std::vector<Entity*>::iterator vIt = purgeEntities.begin();
	while (vIt != purgeEntities.end()) {
		(*vIt)->Destroy();
		entities.remove(*vIt);
		vIt = purgeEntities.erase(vIt);
	}
}

void GameWorld::AddEntity(Entity *entity) {
	entities.push_back(entity);
}

void GameWorld::RemoveEntity(Entity* entity) {
	purgeEntities.push_back(entity);
}