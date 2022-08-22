#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "types.hpp"

#define EVENT_COUNT 1

enum Event
{
    EVENT_TEST
};

typedef std::vector<std::vector<FuncP>> EventTable;

namespace event
{
    void hook(Event e, FuncP f);
    void fire(Event e);
}