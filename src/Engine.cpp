#include "Engine.hpp"

#include <iostream>
#include "Entity.hpp"
#include "Game.hpp"

float Engine::gravity = 0.2;

void Engine::setGravity(float gravity) {
	gravity = gravity;
}

void Engine::ApplyGravity(Entity *entity)
{
	int force = entity->weight * gravity;
	entity->Move(entity->velocity.x, force);
}