#pragma once

#include <functional>
#include <list>

#include "SFML/Graphics.hpp"

class Tools {
	static bool waiting;
	static int waitUntil;

public:
	struct AnimationInfo {
		int count;
		sf::Texture *idleAnim;
		sf::Texture *leftAnim;
		sf::Texture *rightAnim;
		sf::Texture *fallAnim;
		void setup(int count) {
			this->count = count;
			idleAnim = (sf::Texture*)malloc(sizeof(sf::Texture) * count);
			leftAnim = (sf::Texture*)malloc(sizeof(sf::Texture) * count);
			rightAnim = (sf::Texture*)malloc(sizeof(sf::Texture) * count);
			fallAnim = (sf::Texture*)malloc(sizeof(sf::Texture) * count);
		}
	};

	struct Animation {

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

	static int getFrames(int ms);

	static void ExecuteFor(int ms, std::function<void()> func, 
		std::function<void()> endfunc, std::string id);

	static void WaitAndExec(int ms, std::function<void()> func, std::string id);

	static void LogicUpdate();

private:
	static std::list<Task> tasks;
};