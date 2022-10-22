#include "component/animator.hpp"

#include "object/object.hpp"
#include "../../filebuilder/include/filereader.hpp"

#include <math.h>
#include <SFML/Graphics.hpp>
#include <iostream>

Animator::Animator(Object* parent)
    : Component(parent)
    , m_currentFrame(0)
    , m_lastFrame(-1)
{}

void Animator::update(const sf::Time& delta)
{
    m_elapsed += delta;

    const Frame& frame = m_animation.frames[m_currentFrame];

    if (m_elapsed.asMilliseconds() >= frame.duration)
    {
        m_lastFrame = m_currentFrame;

        if (m_currentFrame == m_animation.frames.size() - 1)
        {
            m_currentFrame = 0;
        }
        else
            m_currentFrame++;

        m_elapsed = sf::Time::Zero;
    }

    if (m_currentFrame == m_lastFrame)
        return;

    m_tex.loadFromImage(frame.img);
    m_parent->m_sprite.setTexture(m_tex);
}

bool Animator::load(const std::string& path)
{
    FileReader reader(path);

    const uint32_t& frameCount = reader.getField<uint32_t>("inf", "count");
    for (uint32_t i = 0; i < frameCount; i++)
    {
        const std::string sect = "f" + std::to_string(i);

        const uint32_t& width = reader.getField<uint32_t>(sect, "w");
        const uint32_t& height = reader.getField<uint32_t>(sect, "h");
        const std::vector<uint8_t>& pxData = reader.getField<std::vector<uint8_t>>(sect, "px");

        sf::Image img;
        img.create(width, height, pxData.data());

        const uint32_t& duration = reader.getField<uint32_t>(sect, "dur");

        m_animation.frames.push_back({ img, duration });
    }

    return true;
}