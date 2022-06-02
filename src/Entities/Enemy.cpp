#include <iostream>

#include "Game.hpp"
#include "GameWorld.hpp"
#include "Entities/Enemy.hpp"
#include "Entities/Player.hpp"
#include "Events.hpp"

Enemy::Enemy() {
	moveSpeed = 1;
	name = "enemy";
	jumpSpeed = 5;
	weight = 50;
	health = 100;
	Events::HookTo(PlayerAttacked, [this]() { OnPlayerAttacked(); });
	if (Game::getInstance().isReady()) Setup();
}

void Enemy::Die() {
	//Game::getInstance().getWorld().RemoveEntity(this);
}

void Enemy::OnPlayerAttacked() {
	Player& player = *Game::getInstance().player;
	if (!inXRangeOf(player, 50)) return;
	int x = 5;
	int playerX = player.getX();
	if (playerX > getX()) x = -x;
	jumping = true;
	registerColl = false;
	Tools::ExecuteFor(200, [this, x]() -> void {
		Move(x, -2.5);
		}, [this]()->void {jumping = false; registerColl = true; }, id);
	health -= player.getCurrentWeapon().getDamage();
}

void Enemy::UniqueUpdate() {
	Player& player = *Game::getInstance().player;
	int playerX = player.getX();
	sf::Vector2f movement;
	if (playerX > getX()) 
		movement = sf::Vector2f(moveSpeed, 0);
	if (playerX < getX())
		movement = sf::Vector2f(-moveSpeed, 0);
	Move(movement);
}

void Enemy::AnimUpdate() {
	if (velocity.x == 0) setAnim("idle");
	if (velocity.x == -moveSpeed) setAnim("walkLeft");
	if (velocity.x == moveSpeed) setAnim("walkRight");
	AnimatedEntity::AnimUpdate();
}

void Enemy::OnPlayerCollision() {
}