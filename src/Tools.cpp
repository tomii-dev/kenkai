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
std::list<Tools::Task> Tools::tasks;

Tools::AnimationInfo Tools::GetAnimsById(std::string id) {
	AnimationInfo anims;

	for (int i = 0; i < 4; i++) {
		sf::Texture idleTexture;
		idleTexture.loadFromFile("assets/animations/" + id + "/idle/" + std::to_string(i + 1) + ".png");
		anims.idleAnim[i] = idleTexture;
		sf::Texture leftTexture;
		leftTexture.loadFromFile("assets/animations/" + id + "/left/" + std::to_string(i + 1) + ".png");
		anims.leftAnim[i] = leftTexture;
		sf::Texture rightTexture;
		rightTexture.loadFromFile("assets/animations/" + id + "/right/" + std::to_string(i + 1) + ".png");
		anims.rightAnim[i] = rightTexture;
		sf::Texture fallTexture;
		fallTexture.loadFromFile("assets/animations/" + id + "/idle/1.png");
		anims.fallAnim[i] = fallTexture;
	}

	return anims;
}

void Tools::WaitAndExec(int ms, std::function<void()> func, std::string id) { ExecuteFor(ms, []()->void {; }, func, id); }

void Tools::ExecuteFor(int ms, std::function<void()> func, std::function<void()> endFunc, std::string id) {
	if (ms != NULL) {
		int inc = Game::totalFrame;
		int endFrame = floor(ms * ((float)Properties::frameRate / 1000.0));
		if (!tasks.empty()) {
			std::list<Task>::iterator it;
			int prevTaskEnd = 0;
			for (it = tasks.begin(); it != tasks.end(); it++) {
				if ((*it).id == id) prevTaskEnd = (*it).endFrame;
			}
			if (prevTaskEnd > 0) inc = prevTaskEnd;
		}
		endFrame += inc;
		waiting = true;
		Task task;
		task.endFrame = endFrame;
		task.exec = func;
		task.endExec = endFunc;
		task.id = id;
		tasks.push_back(task);
		return;
	}
	std::list<Task>::iterator it;
	for (it = tasks.begin(); it != tasks.end();) {
		(*it).exec();
		if ((*it).endFrame <= Game::totalFrame) {
			(*it).endExec();
			it = tasks.erase(it);
		}
		else it++;
	}
	if (tasks.empty()) waiting = false;
}

void Tools::LogicUpdate() {
	if (waiting) ExecuteFor(NULL, NULL, NULL, "");
}