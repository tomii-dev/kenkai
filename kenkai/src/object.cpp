#include "object.hpp"

#include <iostream>

#include "game.hpp"

Object::Object(const char* name, World* world)
    : m_name    (name),
      m_world   (world)
{}

void Object::setTexture(const char* path)
{
    m_texture.loadFromFile(path);
    m_sprite.setTexture(m_texture);
}

void Object::update(int deltaTime)
{
    // update state
    if (m_sprite.getPosition().y < m_world->getGroundLevel())
        setState(OBJECT_INAIR);
    else
        setState(OBJECT_ONGROUND);

    if (m_velocity.x > 0)
        addState(OBJECT_MOVINGRIGHT);
    else
        addState(OBJECT_MOVINGLEFT);

    // run tasks 
    std::vector<Task>::iterator it;
    for(it = m_tasks.begin(); it != m_tasks.end();)
    {
        it->func();
        if(Game::getTime() >= it->start + it->duration)
        {
            if(it->endFunc) it->endFunc();
            it = m_tasks.erase(it);
        } else it++;
    }

    m_sprite.move(m_velocity * (float)deltaTime);
    m_velocity = Vec2();
}

float Object::getWeight()
{
    return m_weight;
}

State Object::getState()
{
    return m_state;
}

void Object::setState(State state)
{
    m_state = state;
}

void Object::addState(State state)
{
    m_state |= state;
}

void Object::addTask(int duration, Func f, Func endF)
{
    const int time = Game::getTime();
    m_tasks.push_back(Task{ time, duration, f, endF });
}

Vec2 Object::getPosition()
{
    const Vec2 spritePos(m_sprite.getPosition());
    return Vec2(spritePos.x, -spritePos.y);
}

void Object::setPosition(float x, float y)
{
    m_sprite.setPosition(x, y);
}

void Object::move(float x, float y)
{
    m_sprite.move(x, y);
}

const sf::Sprite& Object::getSprite()
{
    return m_sprite;
}

const char* Object::getName()
{
    return m_name;
}