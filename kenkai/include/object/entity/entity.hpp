#pragma once

#include "object/object.hpp"

class Animator;

// should never be instantiated directly
class Entity : public Object
{
public:
    inline const uint32_t& health() { return m_health; }

    virtual void update(const sf::Time& delta) override;

    void jump();
protected:
    Entity();

    Animator* m_animator;
    float m_moveSpeed;
private:
    uint32_t m_health;
    bool m_jumping;
};