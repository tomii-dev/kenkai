#include "entity.hpp"

#include <iostream>

#include "world.hpp"
#include "types.hpp"
#include "game.hpp"

Entity::Entity(const char* name, World* world, float moveSpeed, float jumpSpeed, float jumpHeight) 
    : Object        (name, world),
      m_moveSpeed   (moveSpeed),
      m_jumpSpeed   (jumpSpeed),
      m_jumpHeight  (jumpHeight)
{}

void Entity::update(int deltaTime)
{    
    if (getState() & ENTITY_JUMPING)
        m_velocity.y = -1;
    else 
        m_velocity.y = 0;

    m_velocity *= Vec2(m_moveSpeed, m_jumpSpeed);

    Object::update(deltaTime);
}

void Entity::jump(int deltaTime)
{
    const State state = getState();
    if(state & ENTITY_JUMPING || state & ENTITY_INAIR)
        return;

    const int duration = (m_jumpHeight / m_jumpSpeed) * deltaTime;
    addTask(duration, [this]() { setState(ENTITY_JUMPING); });
}