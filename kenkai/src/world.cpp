#include "world.hpp"

#include <iostream>

#include "entity.hpp"

World::World() : m_gravity(1.f), m_groundLevel(400.f)
{}

World::~World()
{
    for(Entity* entity : m_entities)
        delete entity;
}

void World::update(float deltaTime)
{
    for(Entity* entity : m_entities)
    {
        // physics
        if(entity->getState() & ENTITY_INAIR)
            entity->move(0, m_gravity * entity->getWeight());

        entity->update(deltaTime);
    }
}

void World::render(sf::RenderWindow& window)
{
    for(Entity* entity : m_entities)
        window.draw(entity->getSprite());
}

float World::getGroundLevel()
{
    return m_groundLevel;
}