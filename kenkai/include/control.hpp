#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <map>

class Object;

class Control
{
public:
    void sendSfmlKey(const sf::Keyboard::Key& key, bool pressed);
    void mouseClick();
    void update();
    inline void setObject(Object* obj) { m_object = obj; }

private:
    enum Input
    {
        INPUT_LEFT,
        INPUT_RIGHT,
        INPUT_DOWN,
        INPUT_JUMP,
        INPUT_ATTACK
    };
    
    // the object being controlled
    Object* m_object;

    std::map<Input, bool> m_inputs;

    // TODO: allow for customisation
    std::map<sf::Keyboard::Key, Input> m_keyControls = {
        {sf::Keyboard::A, INPUT_LEFT},
        {sf::Keyboard::D, INPUT_RIGHT},
        {sf::Keyboard::S, INPUT_DOWN},
        {sf::Keyboard::Space, INPUT_JUMP}
    };

    void doInput(const Input& input, bool pressed);
};