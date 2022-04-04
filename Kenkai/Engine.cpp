#include "Engine.hpp"

#include <iostream>
#include "Entity.hpp"

void Engine::ApplyGravity(std::list<Entity*> entities) {
	std::list<Entity*>::iterator it;
	for (it = entities.begin(); it != entities.end(); it++) {
		(*it)->Move(sf::Vector2f(0, 3));
	}
}