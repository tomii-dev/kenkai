#include "object.hpp"

#include <iostream>

#include "game.hpp"

Object::Object(const char* name, World* world)
    : m_name    (name),
      m_world   (world)
{}

void Object::setTexture(const char* path)
{
    m_texture.loadFromFile(path, sf::IntRect(200, 200, 100, 100));
    m_sprite.setTexture(m_texture);
}

void Object::update()
{
    // run tasks
    std::vector<Task>::iterator it;
    for(it = m_tasks.begin(); it != m_tasks.end();)
    {
        it->func();
        std::cout << Game::getFrame() << std::endl;
        if(Game::getFrame() >= it->startFrame + it->duration)
        {
            if(it->endFunc) it->endFunc();
            it = m_tasks.erase(it);
        } else it++;
    }
}

void Object::addTask(unsigned int duration, Func f, Func endF)
{
    const unsigned int frame = Game::getFrame();
    m_tasks.push_back(Task{ frame, duration, f, endF });
}

void Object::setPosition(float x, float y)
{
    m_sprite.setPosition(x, y);
}

void Object::move(float x, float y)
{
    m_sprite.move(x, y);
}

const sf::Sprite& Object::getSprite()
{
    return m_sprite;
}

const char* Object::getName()
{
    return m_name;
}