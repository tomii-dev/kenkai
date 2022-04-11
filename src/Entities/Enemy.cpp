#include <iostream>

#include "Game.hpp"
#include "Entities/Enemy.hpp"
#include "Entities/Player.hpp"

Enemy::Enemy() {
	moveSpeed = 1;
	name = "enemy";
	jumpSpeed = 5;
	weight = 50;
}

void Enemy::UniqueUpdate() {
	int playerX = Game::player.getX();
	sf::Vector2f movement;
	if (playerX > getX()) 
		movement = sf::Vector2f(moveSpeed, 0);
	if (playerX < getX())
		movement = sf::Vector2f(-moveSpeed, 0);
	Move(movement);
}

void Enemy::OnPlayerCollision() {
	int x = 5;
	int playerX = Game::player.getX();
	if (playerX > getX()) x = -x;
	jumping = true;
	registerColl = false;
	Tools::ExecuteFor(200, [this, x]() -> void{
		Move(x, -2.5);
		}, [this]()->void {jumping = false; registerColl = true; }, name);
}