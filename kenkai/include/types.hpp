#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

typedef sf::Vector2f Vec2;
typedef void(*FuncP)();
typedef std::function<void()> Func;

inline Vec2 operator*(const Vec2& left, const Vec2& right)
{
    return Vec2(left.x * right.x, left.y * right.y);
}

inline Vec2 operator*=(Vec2& left, const Vec2& right)
{
    return left = left * right;
}

struct Task
{
    int start;
    int duration;
    Func func;
    Func endFunc;
};