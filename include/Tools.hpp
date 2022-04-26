#pragma once

#include <functional>
#include <list>
#include <vector>

#include "SFML/Graphics.hpp"
#include "AnimatedEntity.hpp"

class Tools {
	static bool waiting;
	static int waitUntil;
public:
	struct AnimationInfo {
		std::string name;
		int count;
		std::vector<std::string> frames;
		/*int count;
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
		}*/
	};

	struct Animation {
		std::string name;
		int count;
		std::vector<sf::Texture> frames;
		Animation(std::string name, int count, std::vector<sf::Texture> frames) :
			name(name), count(count), frames(frames) {}
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

	//static AnimationInfo GetAnimsById(std::string id);

	static void SetupAnimsFor(AnimatedEntity const &entity);

	static int getFrames(int ms);

	static void ExecuteFor(int ms, std::function<void()> func, 
		std::function<void()> endfunc, std::string id);

	static void WaitAndExec(int ms, std::function<void()> func, std::string id);

	static void LogicUpdate();
	static void DeserializeAnim(std::string path, Animation* anim);

private:
	static std::list<Task> tasks;
};