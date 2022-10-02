#include "object.hpp"

/* virtual */ void Object::update(const sf::Time& delta)
{
    for(const auto& component : m_components)
        component->update(delta);
    
    m_sprite.move(m_velocity);
}