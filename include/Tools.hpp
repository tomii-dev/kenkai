#pragma once

#include <functional>
#include <queue>

#include "SFML/Graphics.hpp"

class Tools {
	static bool waiting;
	static int waitUntil;
	static void SortTasks();

public:
	struct AnimationInfo {
		sf::Texture idleAnim[4];
		sf::Texture leftAnim[4];
		sf::Texture rightAnim[4];
		sf::Texture fallAnim[4];
	};

	struct PlayerConfig {
		std::string username;
		PlayerConfig(std::string _username) {
			username = _username;
		}
	};

	struct Task {
		int endFrame;
		std::string id;
		std::function<void()> exec;
		std::function<void()> endExec;
	};

	static AnimationInfo GetAnimsById(std::string id);

	static void ExecuteFor(int ms, std::function<void()> func, 
		std::function<void()> endfunc, std::string id);

	static void WaitAndExec(int ms, std::function<void()> func, std::string id);

	static void LogicUpdate();

private:
	static std::queue<Task> tasks;
};