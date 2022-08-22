#pragma once

#include "entity.hpp"

#include <SFML/Graphics.hpp>

class World;

class Player : public Entity
{
public:

    // name param will be overriden and set to "player", this param only
    // exists to comply with the addEntity method in World
    Player(const char* name, World* world);

    void update(int deltaTime) override;
};