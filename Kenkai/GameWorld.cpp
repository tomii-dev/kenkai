#include <iostream>

#include "GameWorld.hpp"
#include "Entity.hpp"
#include "AnimatedEntity.hpp"

GameWorld::GameWorld() {
	AnimatedEntity balls;
	entities.push_back(balls);
	std::cout << "BALLS" << std::endl;
}