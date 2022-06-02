#include <iostream>
#include "Events.hpp"

std::list<Events::Event> Events::events;

void Events::RegisterEvents() {
	for (int i = BEGIN+1; i != END; i++) {
		Event event;
		event.id = (EventId)i;
		events.push_back(event);
	}
}

void Events::HookTo(EventId id, std::function<void()> f) {
	std::list<Event>::iterator it;
	for (it = events.begin(); it != events.end(); it++)
		if ((*it).id == id)
			(*it).Hook(f);
}

void Events::Fire(EventId id){
	std::list<Event>::iterator it;
	for (it = events.begin(); it != events.end(); it++)
		if ((*it).id == id) 
			(*it).Fire();
}