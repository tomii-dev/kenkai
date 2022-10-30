#pragma once

#include "object/object.hpp"

class Animator;
class Collider;
class Weapon;

// should never be instantiated directly
class Entity : public Object
{
public:
    Entity();

    inline const uint32_t& health() { return m_health; }
    inline void canJump(bool val) { m_canJump = val; }

    virtual void update(const sf::Time& delta) override;

    virtual void attack();

    void jump();
protected:
    Animator* m_animator;
    Collider* m_collider;

    float m_moveSpeed;
    uint16_t m_jumpForce;

    virtual void onCollision(Object* obj);
    virtual void onAttacked(Weapon* wep);
private:
    uint32_t m_health;
    bool m_jumping;
    bool m_canJump;

    enum LookDirection
    {
        LOOK_LEFT,
        LOOK_RIGHT
    } m_lookDirection;
};