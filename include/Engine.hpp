#pragma once

#include <list>

class Entity;

class Engine {
	static float m_gravity;
public:
	static void ApplyGravity(Entity* entity);
	static void setGravity(float gravity);
};