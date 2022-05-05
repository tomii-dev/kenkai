#include <iostream>
#include "Events.hpp"

std::list<Events::Event> Events::events;
std::string Events::_events[] = {
	"GameReady",
	"MousePressed",
	"PlayerAttacked",
	"ShiftPressed",
	"ShiftReleased"
};

void Events::RegisterEvents() {
	for (int i = 0; i < sizeof(_events) / sizeof(_events[0]); i++) {
		Event event;
		event.id = _events[i];
		events.push_back(event);
	}
}

void Events::HookTo(std::string id, std::function<void()> f) {
	std::list<Event>::iterator it;
	for (it = events.begin(); it != events.end(); it++)
		if ((*it).id == id)
			(*it).Hook(f);
}

void Events::Fire(std::string id){
	std::list<Event>::iterator it;
	for (it = events.begin(); it != events.end(); it++)
		if ((*it).id == id) 
			(*it).Fire();
}