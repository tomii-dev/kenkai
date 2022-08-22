#include "event.hpp"

EventTable g_eventTable(EVENT_COUNT);

void event::hook(Event e, FuncP f)
{
    g_eventTable[e].push_back(f);
}

void event::fire(Event e)
{
    for(FuncP f : g_eventTable[e])
        f();
}