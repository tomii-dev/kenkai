#include "Entities/Player.hpp"
#include "Game.hpp"
#include "Tools.hpp"

Player::Player(Tools::PlayerConfig config) {
	weight = 50;
	name = "player";
	username = config.username;
}

void Player::Jump() {
	Tools::Wait(2000, [this]() -> void {
		movement = sf::Vector2f(0, -0.5);
		});
}