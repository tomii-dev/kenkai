#pragma once

#include "state.hpp"
#include "types.hpp"

class World;

// base object class, should not be instantiated directly
class Object
{
private:
    const char* m_name;
    State m_state;
    sf::Texture m_texture;
    float m_weight = 20.f;
    std::vector<Task> m_tasks;
protected:
    Vec2 m_velocity;
    sf::Sprite m_sprite;
    World* m_world;
    void setTexture(const char* path);
    void setState(State state);
    void addState(State state);

    // function to be used by derivative classes to add
    // tasks to the underlying object's task vector
    void addTask(int duration, Func f, Func endF = nullptr);

public:
    Object(const char* name, World* world = nullptr);
    virtual void update(int deltaTime);
    const sf::Sprite& getSprite();
    const char* getName();
    Vec2 getPosition();
    void setPosition(float x, float y);
    void move(float x, float y);
    float getWeight();
    State getState();
};