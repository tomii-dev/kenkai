#pragma once

#include <iostream>
#include <functional>

#include "SFML/Graphics.hpp"
#include "Properties.hpp"
#include "Game.hpp"
#include "Tools.hpp"

bool Tools::waiting = false;
int Tools::waitUntil = 0;
std::function<void()> Tools::exec;

Tools::AnimationInfo Tools::GetAnimsById(std::string id) {
	AnimationInfo anims;

	for (int i = 0; i < 7; i++) {
		sf::Texture texture;
		texture.loadFromFile("assets/animations/" + id + "/idle/" + std::to_string(i + 1) + ".png");
		anims.idleAnim[i] = texture;
		//texture.loadFromFile("assets/animations/" + id + "/left/" + std::to_string(i + 1) + ".png");
		//anims.leftAnim[i] = texture;
		//texture.loadFromFile("assets/animations/" + id + "/right/" + std::to_string(i + 1) + ".png");
		//anims.rightAnim[i] = texture;
		sf::Texture fallTexture;
		fallTexture.loadFromFile("assets/animations/" + id + "/idle/1.png");
		anims.fallAnim[i] = fallTexture;
	}

	return anims;
}

void Tools::Wait(int ms, std::function<void()> func) {
	if (!waiting) {
		waiting = true;
		waitUntil = Game::totalFrame + floor(ms * ((float)Properties::frameRate / 1000.0));
		exec = func;
		return;
	}
	func();
	if (Game::totalFrame > waitUntil) {
		waiting = false;
		waitUntil = 0;
		std::cout << "waited 2000ms" << std::endl;
	}
}

void Tools::LogicUpdate() {
	if (waiting) Wait(0, exec);
}