#pragma once

#include <string>
#include <list>
#include <functional>

enum EventId{
	BEGIN,
	GameReady, 
	MousePressed, 
	PlayerAttacked,
	ShiftPressed,
	ShiftReleased,
	EscPressed,
	MouseMoved,
	END
};

class Events {
	struct Event {
		EventId id;
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
	static std::list<Event> events;
public:
	static void RegisterEvents();
	static void HookTo(EventId id, std::function<void()> f);
	static void Fire(EventId id);
};
