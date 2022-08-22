#pragma once

#include "types.hpp"

class World;

// base object class, should not be instantiated directly
class Object
{
private:
    const char* m_name;
    sf::Texture m_texture;
    std::vector<Task> m_tasks;
protected:
    sf::Sprite m_sprite;
    World* m_world;
    void setTexture(const char* path);

    // function to be used by derivative classes to add
    // tasks to the underlying object's task vector
    void addTask(unsigned int duration, Func f, Func endF = nullptr);

public:
    Object(const char* name, World* world = nullptr);
    virtual void update();
    const sf::Sprite& getSprite();
    const char* getName();
    void setPosition(float x, float y);
    void move(float x, float y);
};