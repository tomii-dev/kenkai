#pragma once

#include <functional>
#include <list>
#include <vector>
#include <map>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp >
#include <boost/archive/binary_iarchive.hpp>

#include "SFML/Graphics.hpp"

class AnimatedEntity;

class Tools {
	static bool waiting;
	static int waitUntil;
public:
	struct AnimationInfo {
		std::string name;
		int count;
		std::vector<std::string> frames;
		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version) {
			ar& name;
			ar& count;
			ar& frames;
		}
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

	static void SetupAnimsFor(AnimatedEntity* entity);

	static int getFrames(int ms);

	static void ExecuteFor(int ms, std::function<void()> func, 
		std::function<void()> endfunc, std::string id);

	static void WaitAndExec(int ms, std::function<void()> func, std::string id);

	static void LogicUpdate();

private:
	static std::list<Task> tasks;
};