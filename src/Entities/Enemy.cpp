#include <iostream>

#include "Game.hpp"
#include "Entities/Enemy.hpp"
#include "Entities/Player.hpp"

Enemy::Enemy() {
	std::cout << "enemy instantiated" << std::endl;
	moveSpeed = 1;
	name = "enemy";
}

void Enemy::UniqueUpdate() {
	Tools::ExecuteFor(1000, [this]() -> void {
		left = true;
		}, [this]() -> void { left = false; }, name);
	Tools::ExecuteFor(1000, [this]() -> void {
		right = true;
		}, [this]() -> void { right = false; }, name);
}

void Enemy::OnPlayerCollision() {
	Game::player.health -= 1;
}