#include <iostream>

#include "Entities/Player.hpp"
#include "Game.hpp"
#include "Tools.hpp"

Player::Player(Tools::PlayerConfig config) {
	weight = 100;
	name = "player";
	username = config.username;
	moveSpeed = 2.0;
	health = 100;
}

void Player::Jump() {
	if (!canJump) return;
	canJump = false;
	jumping = true;
	inAir = true;
	Tools::ExecuteFor(200, [this]() -> void {
		Move(0, -3);
		}, [this]() ->void {jumping = false; });
	Tools::ExecuteFor(200, []() -> void {; }, [this]()->void {canJump = true; });
}