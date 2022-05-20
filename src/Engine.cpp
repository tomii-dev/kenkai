#include "Engine.hpp"

#include <iostream>
#include "Entity.hpp"
#include "Game.hpp"

float Engine::m_gravity = 0.2;

void Engine::setGravity(float gravity) {
	m_gravity = gravity;
}

void Engine::ApplyGravity(Entity *entity)
{
	int force = entity->weight * m_gravity;
	entity->Move(entity->velocity.x, force);
}