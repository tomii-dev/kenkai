#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

class Object;

typedef sf::Vector2f Vec2;
typedef void(*FuncP)();
typedef std::function<void()> Func;

struct Task
{
    unsigned int startFrame;
    unsigned int duration;
    Func func;
    Func endFunc;
};