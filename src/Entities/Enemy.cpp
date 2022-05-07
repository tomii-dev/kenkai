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
	Events::HookTo("PlayerAttacked", [this]() { OnPlayerAttacked(); });
	if (Game::ready) Setup();
}

void Enemy::Die() {
	Game::world.RemoveEntity(this);
}

void Enemy::OnPlayerAttacked() {
	if (!inXRangeOf(Game::player, 50)) return;
	int x = 5;
	int playerX = Game::player.getX();
	if (playerX > getX()) x = -x;
	jumping = true;
	registerColl = false;
	Tools::ExecuteFor(200, [this, x]() -> void {
		Move(x, -2.5);
		}, [this]()->void {jumping = false; registerColl = true; }, id);
	health -= Game::player.getCurrentWeapon().getDamage();
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

void Enemy::AnimUpdate() {
	if (velocity.x == 0) setAnim("idle");
	if (velocity.x == -moveSpeed) setAnim("walkLeft");
	if (velocity.x == moveSpeed) setAnim("walkRight");
	AnimatedEntity::AnimUpdate();
}

void Enemy::OnPlayerCollision() {
}