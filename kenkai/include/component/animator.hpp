#pragma once

#include "component.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

class Animator : public Component
{
public:
    Animator(Object* parent);

    void update(const sf::Time& delta) override;
    bool load(const std::string& path);
private:
    struct Frame
    {
        const sf::Image img;
        const uint32_t duration;
    };

    struct Animation
    {
        std::vector<Frame> frames;
        uint32_t duration;
    } m_animation;
    
    sf::Time m_elapsed;
    uint32_t m_currentFrame;
    int32_t m_lastFrame;

    sf::Texture m_tex;
};