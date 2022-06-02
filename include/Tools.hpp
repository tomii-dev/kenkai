#pragma once

#include <functional>
#include <list>
#include <vector>
#include <map>
#include <fstream>
#include <variant>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/variant.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/variant.hpp>

#include "SFML/Graphics.hpp"

#define UI_ELEMENTS "assets/textures/ui/"
#define DATA "assets/data/"
#define PI 3.14159265358979323846

class AnimatedEntity;

class DataNode {
	std::string key;
	boost::variant<std::string, int> value;
public:
	DataNode() {}
	DataNode(const std::string& k) : key(k){}
	std::string getKey() {
		return key;
	}
	void operator =(int v) {
		value = v;
	}
	void operator =(std::string v) {
		value = v;
	}
	template <typename T>
	T getValue(){
		return boost::get<T>(value);
	}
	template<typename Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& key;
		ar& value;
	}
};

class Tools {
	static bool waiting;
	static int waitUntil;
public:
	template <typename T>
	static T FetchData(std::string path, std::string key) {
		std::ifstream ifs(DATA + path, std::ios::in | std::ios::binary);
		boost::archive::binary_iarchive iarch(ifs);
		std::vector<DataNode> data;
		iarch >> data;
		for (DataNode node : data)
			if (node.getKey() == key)
				return node.getValue<T>();
	}
	struct AnimationInfo {
		std::string name;
		int count;
		std::vector<std::string> frames;
		int duration;
		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version) {
			ar& name;
			ar& count;
			ar& frames;
			ar& duration;
		}
	};
	struct Animation {
		std::string name;
		int count;
		std::vector<sf::Texture> frames;
		int duration;
		Animation(std::string name, int count, std::vector<sf::Texture> frames, int duration) :
			name(name), count(count), frames(frames), duration(duration) {}
		Animation() {}
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
	static sf::Vector2f getMousePosition();
	static void setMousePosition(sf::Vector2f pos);
	static int RandomInt(int start, int end);
	static bool InRange(sf::Vector2f pos1, sf::Vector2f pos2, sf::Vector2f offset);
private:
	static std::list<Task> tasks;
};