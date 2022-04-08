#include "Engine.hpp"

#include <iostream>
#include "Entity.hpp"
#include "Game.hpp"

void Engine::ApplyGravity(Entity *entity)
{
	int force = entity->weight * 0.2;
	entity->Move(0, force);
}