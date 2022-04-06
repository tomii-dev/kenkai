#include "Engine.hpp"

#include <iostream>
#include "Entity.hpp"

void Engine::ApplyGravity(Entity *entity)
{
	int force = entity->weight * 0.2;
	entity->Move(sf::Vector2f(0, force));
}