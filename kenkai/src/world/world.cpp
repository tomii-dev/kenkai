#include "world/world.hpp"

World::World(sf::RenderWindow& window) : m_window(window)
{}

void World::update(const sf::Time& delta)
{
    for (const std::unique_ptr<Object>& obj : m_objects)
        obj->update(delta);
}

void World::render()
{
    for (const std::unique_ptr<Object>& obj : m_objects)
        obj->render(m_window);
}