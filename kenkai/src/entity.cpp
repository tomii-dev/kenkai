#include "entity.hpp"

#include <iostream>

#include "world.hpp"
#include "types.hpp"
#include "game.hpp"

Entity::Entity(const char* name, World* world) 
    : Object    (name, world),
      m_canJump (true)
{}

void Entity::update()
{
    // update state
    if(m_sprite.getPosition().y < m_world->getGroundLevel())
        m_state = ENTITY_INAIR;
    else
        m_state = ENTITY_ONGROUND;

    if(m_velocity.x == 1)
        m_state |= ENTITY_MOVINGRIGHT;
    else
        m_state |= ENTITY_MOVINGLEFT;
    
    Object::update();
    
    if(m_state == ENTITY_JUMPING)
        m_velocity.y = -1;
    else m_velocity.y = 0;

    m_sprite.move(m_velocity);
}

void Entity::jump()
{
    if(!m_canJump)
        return;
    m_canJump = false;
    addTask(100, [this](){ m_state = ENTITY_JUMPING; }, [this](){ this->m_canJump = true; });
}

EntityState Entity::getState()
{
    return m_state;
}
