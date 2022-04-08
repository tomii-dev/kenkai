#include <iostream>

#include "Game.hpp"
#include "Entities/Enemy.hpp"
#include "Entities/Player.hpp"

Enemy::Enemy() {
	std::cout << "enemy instantiated" << std::endl;
}

void Enemy::OnPlayerCollision() {
	Game::player.health -= 1;
}