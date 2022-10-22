#include "object/entity/player.hpp"

#include "component/animator.hpp"

Player::Player()
    : m_animator(addComponent<Animator>())
{
    m_animator->load("player.kenk");
}