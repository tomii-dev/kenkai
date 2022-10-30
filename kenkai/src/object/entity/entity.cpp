#include "object/entity/entity.hpp"

#include "component/animator.hpp"
#include "component/collider.hpp"
#include "object/weapon.hpp"
#include "util/filesys.hpp"

#include <iostream>

Entity::Entity() 
    : m_animator(addComponent<Animator>())
    , m_collider(addComponent<Collider>(.75, .75))
    , m_jumpForce(0)
    , m_canJump(true)
{
    m_animator->load(FileSys::animPath() + "player.ken");
    m_animator->setDefaultAnimation("idle");

    m_collider->onCollision()->add([this](Object* obj) { onCollision(obj); });
}

void Entity::update(const sf::Time& delta)
{
    if (m_jumping)
        setVelocityY(m_jumpForce);
    else
        if (m_velocity.x < 0)
        {
            m_animator->setAnimation("walk_left");
            m_lookDirection = LOOK_LEFT;
        }
        else if (m_velocity.x > 0)
        {
            m_animator->setAnimation("walk_right");
            m_lookDirection = LOOK_RIGHT;
        }
        else
            m_animator->setAnimation("idle");

    m_velocity.x *= m_moveSpeed;

    Object::update(delta);
}

void Entity::attack()
{
    if (m_lookDirection == LOOK_LEFT)
        m_animator->playAnimation("attack_left");
    else if (m_lookDirection == LOOK_RIGHT)
        m_animator->setAnimation("attack_right");
}

void Entity::jump()
{
    if (m_jumping || !m_canJump)
        return;

    m_jumping = true;
    m_canJump = false;

    addTask([this]() { m_jumping = false; }, 200);
}

void Entity::onCollision(Object* obj)
{
    if (Weapon* wep = dynamic_cast<Weapon*>(obj))
        onAttacked(wep);
}

void Entity::onAttacked(Weapon* wep)
{
    m_animator->setAnimation("attacked");
    m_health -= wep->damage();
}