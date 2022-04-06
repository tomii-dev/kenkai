#pragma once

#include <iostream>
#include <functional>
#include <queue>

#include "SFML/Graphics.hpp"
#include "Properties.hpp"
#include "Game.hpp"
#include "Tools.hpp"

bool Tools::waiting = false;
int Tools::waitUntil = 0;
std::queue<Tools::Task> Tools::tasks;

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

void Tools::ExecuteFor(int ms, std::function<void()> func) {
	if (waitUntil != tasks.front().endFrame) {
		waiting = true;
		waitUntil = Game::totalFrame + floor(ms * ((float)Properties::frameRate / 1000.0));
		Task task;
		task.endFrame = waitUntil;
		task.exec = func;
		tasks.push(task);
		return;
	}
	tasks.front().exec();
	if (Game::totalFrame > waitUntil) tasks.pop();
	if (tasks.empty()) waiting = false;
}

void Tools::LogicUpdate() {
	if (waiting) ExecuteFor(NULL, NULL);
}