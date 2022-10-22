#pragma once

#include "object/entity/entity.hpp"
#include "component/animator.hpp"

class Player : public Entity
{
public:
    Player();
private:
    Animator* m_animator;
};