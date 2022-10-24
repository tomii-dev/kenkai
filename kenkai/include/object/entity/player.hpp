#pragma once

#include "object/entity/entity.hpp"
#include "component/animator.hpp"

class Player : public Entity
{
public:
    Player();

    void update(const sf::Time& delta) override;
private:
};