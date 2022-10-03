#pragma once

#include "types.hpp"
#include "component/component.hpp"

class Object
{
public:
    enum State
    {
        OBJECT_ONGROUND,
        OBJECT_INAIR
    };

    // must be called by override functions
    virtual void update(const sf::Time& delta);

    inline void render(sf::RenderWindow& window) { window.draw(m_sprite); }

    inline const Vec2& position() { return m_position; }
    inline const int32_t& weight() { return m_weight; }
    inline const State& state() { return m_state; }

    template<typename ComponentType>
    ComponentType* addComponent()
    {
        static_assert(std::is_base_of<Component, ComponentType>::value);

        m_components.push_back(std::make_unique<ComponentType>());
        return m_components.back().get();
    }
private:
    State m_state;
    sf::Sprite m_sprite;
    int32_t m_weight;
    Vec2 m_position;
    Vec2 m_velocity;

    using Components = std::vector<std::unique_ptr<Component>>;
    Components m_components;

    friend class Animator;
};