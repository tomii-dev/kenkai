#include <iostream>

#include "Game.hpp"
#include "Entities/Enemy.hpp"
#include "Entities/Player.hpp"

Enemy::Enemy() {
	std::cout << "enemy instantiated" << std::endl;
	moveSpeed = 1;
	name = "enemy";
}

void Enemy::JumpLoop() {
	jumping = true;
	Tools::ExecuteFor(200, [this]() -> void {
		Move(0, -2);
		}, [this]() ->void {jumping = false; }, name);
	Tools::WaitAndExec(200, [this]()->void { JumpLoop(); }, name);
}
void Enemy::UniqueUpdate() {
	if (canJump && !inAir) {
		canJump = false;
		JumpLoop();
	}
}

void Enemy::OnPlayerCollision() {
	Game::player.health -= 1;
}