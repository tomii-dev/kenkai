#include "component/animator.hpp"

#include "object/object.hpp"
#include "util/image.hpp"
#include "../../filebuilder/include/filereader.hpp"

#include <math.h>
#include <SFML/Graphics.hpp>
#include <iostream>

Animator::Animator(Object* parent)
    : Component(parent)
    , m_anim(nullptr)
    , m_currentFrame(0)
    , m_lastFrame(-1)
{}

void Animator::update(const sf::Time& delta)
{
    m_elapsed += delta;

    if (!m_anim)
        changeAnim(m_defaultAnim);

    const Frame& frame = m_anim->at(m_currentFrame);

    if (m_elapsed.asMilliseconds() >= frame.duration)
    {
        m_lastFrame = m_currentFrame;

        if (m_currentFrame == m_anim->size() - 1)
        {
            m_currentFrame = 0;
            if (m_playOnce)
            {
                m_anim = nullptr;
                m_playOnce = false;
            }
        }
        else
            m_currentFrame++;

        m_elapsed = sf::Time::Zero;
    }

    if (m_currentFrame == m_lastFrame)
        return;

    m_tex.loadFromImage(frame.img);
    m_parent->m_sprite.setTexture(m_tex);

    m_lastFrame = m_currentFrame;
}

bool Animator::load(const std::string& path)
{
    FileReader reader(path);

    for (const std::string& sect : reader.sections())
    {
        if (sect.substr(0, 5) != "anim_")
            continue;

        Animation anim;

        const uint32_t& frameCount = reader.getField<uint32_t>(sect, "count");
        for (uint32_t i = 0; i < frameCount; i++)
        {
            const std::string frameId = "f" + std::to_string(i) + "_";

            const uint32_t& duration = reader.getField<uint32_t>(sect, frameId + "dur");
            const uint32_t& width = reader.getField<uint32_t>(sect, frameId + "w");
            const uint32_t& height = reader.getField<uint32_t>(sect, frameId + "h");
            const std::vector<uint8_t>& pxData = reader.getField<std::vector<uint8_t>>(sect, frameId + "px");

            sf::Image img;
            img.create(width, height, pxData.data());

            anim.push_back({ img, duration });
        }

        m_animations.insert({ sect.substr(5), anim });
    }

    return true;
}

void Animator::setAnimation(const std::string& id)
{
    // animation is playing
    if (m_playOnce)
        return;

    if(!changeAnim(id))
        return;
}

void Animator::setDefaultAnimation(const std::string& id)
{
    if (!m_animations.count(id))
        return;

    m_defaultAnim = id;
}

void Animator::playAnimation(const std::string& id)
{
    if (!changeAnim(id))
        return;

    m_playOnce = true;
}

bool Animator::changeAnim(const std::string& id)
{
    if (&m_animations[id] == m_anim)
        return false;

    // TODO: some sort of graceful error handling
    if (!m_animations.count(id))
        return false;

    m_anim = &m_animations[id];
    m_currentFrame = 0;
    m_lastFrame = -1;
}