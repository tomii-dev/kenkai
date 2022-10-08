#include "component/animator.hpp"

#include "object/object.hpp"

#include <math.h>
#include <SFML/Graphics.hpp>

void Animator::update(const sf::Time& delta)
{
    m_elapsed += delta;
    if(m_elapsed.asMilliseconds() >= m_animation.duration)
        m_elapsed = sf::Time();

    // current frame of anim
    const int32_t ind = floor(m_elapsed.asMilliseconds() / m_interval);
    const Frame frame = m_animation.frames[ind];

    if(ind == m_lastFrame)
        return;
    
    m_lastFrame = ind;

    sf::Texture tex;
    tex.loadFromMemory(frame.data, frame.size);
    m_parent->m_sprite.setTexture(tex);
}

bool Animator::load(const std::string& path)
{
    return true;
}