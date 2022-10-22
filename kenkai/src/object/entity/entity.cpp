#include "object/entity/entity.hpp"

void Entity::update(const sf::Time& delta)
{
    if (m_jumping)
        setVelocityY(1);

    Object::update(delta);
}

void Entity::jump()
{
    if (m_jumping)
        return;

    m_jumping = true;

    addTask([this]() { m_jumping = false; }, 200);
}