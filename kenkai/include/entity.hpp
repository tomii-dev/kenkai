#pragma once

#include <SFML/Graphics.hpp>

#include "object.hpp"
#include "state.hpp"

class World;

class Entity : public Object
{
private:
    float m_moveSpeed;
    float m_jumpSpeed;
    float m_jumpHeight;
protected:
    void jump(int deltaTime);
public:
    Entity(const char* name, World* world = nullptr, float moveSpeed = 1.f, float jumpSpeed = 1.f, float jumpHeight = 20.f);
    void update(int deltaTime) override;
};