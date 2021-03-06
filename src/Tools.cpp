#pragma once

#include <iostream>
#include <functional>
#include <queue>
#include <fstream>
#include <sstream>
#include <random>

#include "SFML/Graphics.hpp"
#include "Properties.hpp"
#include "Game.hpp"
#include "Tools.hpp"
#include "AnimatedEntity.hpp"

bool Tools::waiting = false;
int Tools::waitUntil = 0;
std::list<Tools::Task> Tools::tasks;

void Tools::SetupAnimsFor(AnimatedEntity* entity) {
	std::ostringstream ss;
	ss << "assets/animations/" << entity->name << "/" << entity->name << ".conf";
	std::map<std::string, AnimationInfo> configMap;
	std::ifstream ifs(ss.str(), std::ios::binary);
	boost::archive::binary_iarchive iarch(ifs);
	iarch >> configMap;
	ifs.close();
	std::map<std::string, Animation> tempMap;
	std::map<std::string, AnimationInfo>::iterator it;
	for (it = configMap.begin(); it != configMap.end(); it++) {
		std::vector<sf::Texture> frames;
		for (std::string i : it->second.frames) {
			sf::Texture texture;
			texture.loadFromFile(i);
			frames.push_back(texture);
		}
		Animation anim(it->second.name, it->second.count, frames, it->second.duration);
		tempMap.insert({ it->first.c_str(), anim});
	}
	entity->setAnims(tempMap);
}

int Tools::getFrames(int ms) { return floor(ms * ((float)Properties::frameRate / 1000.0)); }

void Tools::WaitAndExec(int ms, std::function<void()> func, std::string id) { ExecuteFor(ms, []()->void {; }, func, id); }

void Tools::ExecuteFor(int ms, std::function<void()> func, std::function<void()> endFunc, std::string id) {
	if (ms != NULL) {
		int inc = Game::getInstance().getTotalFrame();
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
		if ((*it).endFrame <= Game::getInstance().getTotalFrame()) {
			if((*it).endExec != NULL) 
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

sf::Vector2f Tools::getMousePosition() {
	const sf::RenderWindow& window = Game::getInstance().getWindow();
	return window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

void Tools::setMousePosition(sf::Vector2f pos) {
	const sf::RenderWindow& window = Game::getInstance().getWindow();
	sf::Mouse::setPosition(window.mapCoordsToPixel(pos), window);
}

int Tools::RandomInt(int start, int end) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(start, end);
	return dist(gen);
}

bool Tools::InRange(sf::Vector2f pos1, sf::Vector2f pos2, sf::Vector2f offset){
	offset.x /= 2;
	offset.y /= 2;
	bool xInRange = pos1.x >= (pos2.x - (offset.x)) && pos1.x <= (pos2.x + offset.x);
	bool yInRange = pos1.y >= (pos2.y - offset.y) && pos1.y <= (pos2.y + offset.y);
	return xInRange && yInRange;
}