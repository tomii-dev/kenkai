#pragma once

#include "component.hpp"

#include <vector>

class Animator : public Component
{
public:
    inline Animator(Object* parent) : Component(parent) {}

    void update(const sf::Time& delta) override;
    bool load(const std::string& path);
private:
    struct Frame
    {
        unsigned char* data;
        size_t size;
    };

    struct Animation
    {
        std::vector<Frame> frames;
        uint32_t duration;
    } m_animation;
    
    sf::Time m_elapsed;
    uint32_t m_interval;
    int32_t m_lastFrame;
};