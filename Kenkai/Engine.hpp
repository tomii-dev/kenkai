#pragma once

#include <list>

class Entity;

class Engine {
public:
	static void ApplyGravity(std::list<Entity*> entities);
};