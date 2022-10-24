#include "object/entity/entity.hpp"

#include "component/animator.hpp"

Entity::Entity() : m_animator(addComponent<Animator>())
{}

void Entity::update(const sf::Time& delta)
{
    if (m_jumping)
        setVelocityY(1);

    if (m_velocity.x < 0)
        m_animator->setAnimation("walk_left");
    else if (m_velocity.x > 0)
        m_animator->setAnimation("walk_right");
    else
        m_animator->setAnimation("idle");

    m_velocity.x *= m_moveSpeed;

    Object::update(delta);
}

void Entity::jump()
{
    if (m_jumping)
        return;

    m_jumping = true;

    addTask([this]() { m_jumping = false; }, 200);
}