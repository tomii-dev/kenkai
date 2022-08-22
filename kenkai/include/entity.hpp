#pragma once

#include <SFML/Graphics.hpp>

#include "object.hpp"
#include "state.hpp"

class World;

class Entity : public Object
{
private:
    EntityState m_state;
    float m_weight;
    bool m_canJump;
protected:
    sf::Vector2f m_velocity;
    void jump();
public:
    Entity(const char* name, World* world=nullptr);
    EntityState getState();
    void update() override;
};