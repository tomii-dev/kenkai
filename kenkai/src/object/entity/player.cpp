#include "object/entity/player.hpp"

#include "component/animator.hpp"

Player::Player()
{
    m_moveSpeed = 100;
    m_jumpForce = 300;
}

void Player::update(const sf::Time& delta)
{
    Entity::update(delta);
}