#pragma once

#include "types.hpp"
#include "component/component.hpp"

#include <functional>

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

    inline void setPosition(const Vec2& pos) { m_sprite.setPosition(pos); }
    inline virtual void move(int x, int y) { m_sprite.move(x, -y); }
    inline void setVelocity(int x, int y) { m_velocity = Vec2(x, y); }
    inline void setVelocityX(int x) { m_velocity.x = x; }
    inline void setVelocityY(int y) { m_velocity.y = -y; }

    inline const Vec2& position() { return m_position; }
    inline const uint32_t& weight() { return m_weight; }
    inline const State& state() { return m_state; }

    template<typename ComponentType, typename... Args>
    ComponentType* addComponent(Args... args)
    {
        static_assert(std::is_base_of<Component, ComponentType>::value);

        m_components.push_back(std::make_unique<ComponentType>(this, args...));
        return dynamic_cast<ComponentType*>(m_components.back().get());
    }
protected:
    Vec2 m_velocity;

    void addTask(std::function<void()> f, uint32_t ms);
private:
    State m_state;
    sf::Sprite m_sprite;
    uint32_t m_weight;
    Vec2 m_position;

    using Components = std::vector<std::unique_ptr<Component>>;
    Components m_components;

    friend class Animator;
};