#pragma once

#include "component.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

class Animator : public Component
{
public:
    Animator(Object* parent);

    void update(const sf::Time& delta) override;
    bool load(const std::string& path);

    void setAnimation(const std::string& id);
    void setDefaultAnimation(const std::string& id);
    void playAnimation(const std::string& id);
private:
    struct Frame
    {
        const sf::Image img;
        const uint32_t duration;
    };

    using Animation = std::vector<Frame>;
    std::map<std::string, Animation> m_animations;

    Animation* m_anim;
    std::string m_defaultAnim;

    bool m_playOnce = false;
    
    sf::Time m_elapsed;
    uint32_t m_currentFrame;
    int32_t m_lastFrame;

    sf::Texture m_tex;

    bool changeAnim(const std::string& id);
};