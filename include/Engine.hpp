#pragma once

#include <list>

class Entity;

class Engine {
	static float gravity;
public:
	static void ApplyGravity(Entity* entity);
	static void setGravity(float gravity);
};