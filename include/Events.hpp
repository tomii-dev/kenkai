#pragma once

#include <string>
#include <list>

typedef void (*fp)();

class Events {
	struct Event {
		std::string id;
		std::list<fp> hookedFuncs;
		void Hook(void(&f)()) {
			hookedFuncs.push_back(f);
		}
		void Fire() {
			std::list<fp>::iterator it;
			for (it = hookedFuncs.begin(); it != hookedFuncs.end(); it++)
				(*it)();
		}
	};
	static std::string _events[];
	static std::list<Event> events;
public:
	static void RegisterEvents();
	static void HookTo(std::string id, void(f)());
	static void Fire(std::string id);
};
