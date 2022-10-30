#pragma once

#include "types.hpp"
#include "component/component.hpp"

#include <functional>
#include <algorithm>

class Object
{
public:
    Object(Object* parent = nullptr);

    enum State
    {
        OBJECT_ONGROUND,
        OBJECT_INAIR
    };

    // must be called by override functions
    virtual void update(const sf::Time& delta);

    inline void render(sf::RenderWindow& window) { window.draw(m_sprite); }

    inline void setTexture(const sf::Texture& tex) { m_tex = tex; m_sprite.setTexture(m_tex); }
    inline void setTexture(const sf::Image& img) { m_tex.loadFromImage(img); m_sprite.setTexture(m_tex); }

    void setPosition(const Vec2& pos);
    void setPosition(float x, float y);
    inline virtual void move(int x, int y) { m_sprite.move(x, -y); }
    inline void setVelocity(int x, int y) { m_velocity = Vec2(x, y); }
    inline void setVelocityX(int x) { m_velocity.x = x; }
    inline void setVelocityY(int y) { m_velocity.y = -y; }

    inline const Vec2& worldPosition() { return Vec2(m_sprite.getPosition().x, -m_sprite.getPosition().y); }
    inline const uint32_t& weight() { return m_weight; }
    inline const State& state() { return m_state; }

    template <typename ObjectType, typename ...Args>
    ObjectType* addChild(Args... args)
    {
        static_assert(std::is_base_of<Object, ObjectType>::value);

        m_children.push_back(std::make_unique<ObjectType>(this, args...));
        return dynamic_cast<ObjectType*>(m_children.back().get());
    }

    template <typename ComponentType, typename... Args>
    ComponentType* addComponent(Args... args)
    {
        static_assert(std::is_base_of<Component, ComponentType>::value);

        m_components.push_back(std::make_unique<ComponentType>(this, args...));
        return dynamic_cast<ComponentType*>(m_components.back().get());
    }

    template <typename ComponentType>
    ComponentType* getComponent()
    {
        static_assert(std::is_base_of<Component, ComponentType>::value);

        for (const auto& com : m_components)
            if (ComponentType* component = dynamic_cast<ComponentType*>(com.get()))
                return component;

        return nullptr;
    }
protected:
    Vec2 m_velocity;

    void addTask(std::function<void()> f, uint32_t ms);
private:
    Object* m_parent;
    State m_state;
    sf::Sprite m_sprite;
    uint32_t m_weight;
    sf::Texture m_tex;

    using Components = std::vector<std::unique_ptr<Component>>;
    Components m_components;

    using Children = std::vector<std::unique_ptr<Object>>;
    Children m_children;

    friend class Animator;
    friend class Collider;
};