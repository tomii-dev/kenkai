#pragma once

#include <functional>
#include <queue>

#include "SFML/Graphics.hpp"

class Tools {
	static bool waiting;
	static int waitUntil;

public:
	struct AnimationInfo {
		sf::Texture idleAnim[7];
		sf::Texture leftAnim[6];
		sf::Texture rightAnim[6];
		sf::Texture fallAnim[7];
	};

	struct PlayerConfig {
		std::string username;
		PlayerConfig(std::string _username) {
			username = _username;
		}
	};

	struct Task {
		int endFrame;
		std::function<void()> exec;
	};
	static AnimationInfo GetAnimsById(std::string id);

	static void ExecuteFor(int ms, std::function<void()> func);

	static void LogicUpdate();

private:
	static std::queue<Task> tasks;
};