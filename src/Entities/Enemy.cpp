#include <iostream>

#include "Game.hpp"
#include "Entities/Enemy.hpp"
#include "Entities/Player.hpp"

Enemy::Enemy() {
	std::cout << "enemy instantiated" << std::endl;
	moveSpeed = 1;
}

void Enemy::UniqueUpdate() {
	Tools::ExecuteFor(1000, [this]() -> void {
		left = true;
		}, [this]() -> void { left = false; });
	Tools::ExecuteFor(1000, [this]() -> void {
		right = true;
		}, [this]() -> void { right = false; });

	std::cout << "left: " << left << std::endl;
	std::cout << "right: " << right << std::endl;
}

void Enemy::OnPlayerCollision() {
	Game::player.health -= 1;
}