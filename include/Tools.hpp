#pragma once

#include <iostream>
#include <math.h>
#include <functional>

#include "SFML/Graphics.hpp"

class Tools {
	static bool waiting;
	static int waitUntil;
	static std::function<void()> exec;

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

	static AnimationInfo GetAnimsById(std::string id);

	static void ExecuteFor(int ms, std::function<void()> func);

	static void LogicUpdate();
};