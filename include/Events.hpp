#pragma once

#include <string>
#include <list>
#include <functional>

class Events {
	struct Event {
		std::string id;
		std::list<std::function<void()>> hookedFuncs;
		void Hook(std::function<void()> f) {
			hookedFuncs.push_back(f);
		}
		void Fire() {
			std::list<std::function<void()>>::iterator it;
			for (it = hookedFuncs.begin(); it != hookedFuncs.end(); it++)
				(*it)();
		}
	};
	static std::string _events[];
	static std::list<Event> events;
public:
	static void RegisterEvents();
	static void HookTo(std::string id, std::function<void()> f);
	static void Fire(std::string id);
};
