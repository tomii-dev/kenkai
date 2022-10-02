#pragma once

#include <SFML/System.hpp>

class Object;

class Component
{
public:
    inline Component(Object* parent) : m_parent(parent) {}

    virtual void update(const sf::Time& delta) = 0;
protected:
    Object* m_parent;
};