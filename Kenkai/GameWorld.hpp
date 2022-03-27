#pragma once

#include <list>

class Entity;

class GameWorld {
	std::list <Entity> entities;
public:
	GameWorld();
	void RenderEntities();
};