#include "Entities/Player.hpp"

Player::Player(Tools::PlayerConfig config) {
	name = "player";
	username = config.username;
}