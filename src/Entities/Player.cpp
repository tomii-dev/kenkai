#include <iostream>
#include <format>

#include "Entities/Player.hpp"
#include "Game.hpp"
#include "Tools.hpp"
#include "Events.hpp"
#include "GameWorld.hpp"

Player::Player(Tools::PlayerConfig config) 
	: cursor("cursor", "cursor.png", 20, 20) {
	weight = 50;
	name = "player";
	username = config.username;
	moveSpeed = 2.5;
	health = 100;
	currentWeapon.setDamage(10);
	sprinting = false;
	cursor.setBehaviour([this]()->void {
		this->cursor.setPosition(getPosition() + sf::Vector2f(50, 0));
	});
	Events::HookTo("MousePressed", [this]() {Attack(); });
	Events::HookTo("ShiftPressed", [this]() {sprinting = true; });
	Events::HookTo("ShiftReleased", [this]() {sprinting = false; });
}

void Player::Setup() {
	AnimatedEntity::Setup();
	Game::world.AddUIElement(&cursor);
}

void Player::Attack() {
	Events::Fire("PlayerAttacked");
	setAnim("attackLeft", true);
}

Weapon Player::getCurrentWeapon() { return currentWeapon; }

void Player::UniqueUpdate() {
	if (sprinting) moveSpeed = 5;
	else moveSpeed = 2.5;
}

void Player::AnimUpdate() {
	if (velocity.x == 0) setAnim("idle");
	if (velocity.x == -moveSpeed) setAnim("walkLeft");
	if (velocity.x == moveSpeed) setAnim("walkRight");
	if (velocity.x == -5) setAnim("runLeft");
	if (velocity.x == 5) setAnim("runRight");
	AnimatedEntity::AnimUpdate();
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
		Move(0, -4);
		}, [this]() ->void {jumping = false; }, id);
	Tools::WaitAndExec(100, [this]()->void {canJump = true; }, id);
}