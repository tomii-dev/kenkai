#include <iostream>

#include "Entities/Player.hpp"
#include "Game.hpp"
#include "Tools.hpp"

Player::Player(Tools::PlayerConfig config) {
	weight = 30;
	name = "player";
	username = config.username;
}

void Player::Jump() {
	jumping = true;
	inAir = true;
	Tools::ExecuteFor(200, [this]() -> void {
		Move(0, -2);
		}, [this]() ->void {jumping = false; });
}