#include <iostream>

#include "GameWorld.hpp"
#include "Entity.hpp"
#include "AnimatedEntity.hpp"

GameWorld::GameWorld() {
	std::cout << "world created" << std::endl;
;
}

void GameWorld::RenderEntities() {
	std::list<Entity>::iterator it;
	for (it = entities.begin(); it != entities.end(); it++){
		std::cout << it->name << std::endl;
	}
}