#include "object/object.hpp"

#include "game.hpp"
#include "util/taskmanager.hpp"

/* virtual */ void Object::update(const sf::Time& delta)
{
    for(const auto& component : m_components)
        component->update(delta);
    
    m_sprite.move(m_velocity * delta.asSeconds());
    m_velocity = Vec2();
}

void Object::addTask(TaskManager::Callback callback, uint32_t ms)
{
    Game::get().taskManager().addTask(this, ms, callback);
}