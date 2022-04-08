#include <iostream>

#include "Entities/Player.hpp"
#include "Game.hpp"
#include "Tools.hpp"

Player::Player(Tools::PlayerConfig config) {
	weight = 50;
	name = "player";
	username = config.username;
}

void Player::Jump() {
	Tools::ExecuteFor(200, [this]() -> void {
		Move(sf::Vector2f(0, -0.2));
		});
	Tools::ExecuteFor(200, [this]() -> void {
		Move(sf::Vector2f(0, 0.2));
		});
}