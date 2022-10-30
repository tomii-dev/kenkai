#include "object/object.hpp"

#include "game.hpp"
#include "util/taskmanager.hpp"

Object::Object(Object* parent) 
    : m_parent(parent)
    , m_weight(0)
{}

/* virtual */ void Object::update(const sf::Time& delta)
{
    for (const std::unique_ptr<Object>& child : m_children)
        child->update(delta);

    for(const std::unique_ptr<Component>& component : m_components)
        component->update(delta);
    
    m_sprite.move(m_velocity * delta.asSeconds());
    m_velocity = Vec2();
}

void Object::setPosition(const Vec2& pos)
{
    if (m_parent)
    {
        m_sprite.setPosition(m_parent->worldPosition() + Vec2(pos.x, -pos.y));
        return;
    }

    m_sprite.setPosition(Vec2(pos.x, -pos.y));
}

void Object::setPosition(float x, float y)
{
    if (m_parent)
    {
        m_sprite.setPosition(m_parent->worldPosition() + Vec2(x, -y));
        return;
    }

    m_sprite.setPosition(Vec2(x, -y));
}

void Object::addTask(TaskManager::Callback callback, uint32_t ms)
{
    Game::get().taskManager().addTask(this, ms, callback);
}