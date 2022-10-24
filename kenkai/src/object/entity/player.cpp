#include "object/entity/player.hpp"

#include "component/animator.hpp"

Player::Player()
{
    m_animator->load("player.ken");
    m_moveSpeed = 100;
}

void Player::update(const sf::Time& delta)
{
    Entity::update(delta);
}