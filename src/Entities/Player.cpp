#include <iostream>

#include "Entities/Player.hpp"
#include "Game.hpp"
#include "Tools.hpp"

Player::Player(Tools::PlayerConfig config) {
	weight = 10;
	name = "player";
	username = config.username;
	moveSpeed = 2.0;
	health = 100;
}

void Player::UniqueUpdate() {

}

void Player::Die() {
	sf::Font font;
	font.loadFromFile("assets/fonts/dosis.ttf");
	Game::msg.setString("bruh");
	Game::msg.setFont(font);
	Game::msg.setCharacterSize(50);
	Game::msg.setPosition(400, 300);
	std::cout << "HE DEAD" << std::endl;
}

void Player::Jump() {
	if (!canJump || inAir) return;
	canJump = false;
	jumping = true;
	inAir = true;
	Tools::ExecuteFor(200, [this]() -> void {
		Move(0, -3);
		}, [this]() ->void {jumping = false; }, name);
	Tools::WaitAndExec(100, [this]()->void {canJump = true; }, name);
}