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

void Tools::SortTasks() {
	int i = 0;
	int* frameArr = new int[tasks.size()];
	std::array<Task, tasks.size()> 
	while (!tasks.empty()) {
		taskArr[i] = tasks.front();
		frameArr[i] = tasks.front().endFrame;
		tasks.pop();
		i++;
	}
	std::sort(frameArr.begin())
}

void Tools::WaitAndExec(int ms, std::function<void()> func, std::string id) { ExecuteFor(ms, []()->void {; }, func, id); }

void Tools::ExecuteFor(int ms, std::function<void()> func, std::function<void()> endFunc, std::string id) {
	if (ms != NULL) {
		int endFrame = floor(ms * ((float)Properties::frameRate / 1000.0));
		if (!tasks.empty()) {
			std::queue<Tools::Task> tmpQ = tasks;
			Task prevTask;
			while (!tmpQ.empty()) {
				Task cTask = tmpQ.front();
				if (cTask.id == id) prevTask = cTask;
				tmpQ.pop();
			}
			if (prevTask.endFrame < 0) endFrame += tasks.front().endFrame;
			else endFrame += prevTask.endFrame;
		}
		else endFrame += Game::totalFrame;
		waiting = true;
		Task task;
		task.endFrame = endFrame;
		task.exec = func;
		task.endExec = endFunc;
		tasks.push(task);
		SortTasks();
		return;
	}
	func();
	if (Game::totalFrame > tasks.front().endFrame) {
		tasks.pop();
		endFunc();
	}
	if (tasks.empty()) waiting = false;
}

void Tools::LogicUpdate() {
	if (waiting) ExecuteFor(NULL, tasks.front().exec, tasks.front().endExec, "");
}