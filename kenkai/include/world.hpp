#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <type_traits>
#include <exception>

#include "entity.hpp"

class World
{
private:
    std::vector<Entity*> m_entities;
    float m_gravity;
    float m_groundLevel;
public:
    World();
    ~World();
    template <typename EntityType>
    EntityType* addEntity(const char* name = "")
    {
        if(!std::is_base_of<Entity, EntityType>())
            throw std::runtime_error("type specified is not an entity!");

        EntityType* entity = new EntityType(name, this);
        m_entities.push_back(entity);
        return entity;
    }
    void update();
    void render(sf::RenderWindow& window);
    float getGroundLevel();
};