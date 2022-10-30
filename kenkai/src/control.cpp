#include "control.hpp"

#include "object/object.hpp"
#include "object/entity/entity.hpp"

#include <iostream>

void Control::sendSfmlKey(const sf::Keyboard::Key& key, bool pressed)
{
    if (!m_keyControls.count(key))
        return;

    doInput(m_keyControls[key], pressed);
}

void Control::mouseClick()
{
    doInput(INPUT_ATTACK, true);

}

void Control::doInput(const Input& input, bool pressed)
{
    switch (input)
    {
    case INPUT_JUMP:
    {
        // player has to release jump
        if (m_inputs[input])
            break;

        if (Entity* ent = dynamic_cast<Entity*>(m_object))
            ent->jump();
        break;
    }
    case INPUT_ATTACK:
        if (Entity* ent = dynamic_cast<Entity*>(m_object))
            ent->attack();
        return;
    default:
        break;
    }
    m_inputs[input] = pressed;
}

void Control::update()
{
    if (m_inputs[INPUT_LEFT])
        m_object->setVelocityX(-1);
    if (m_inputs[INPUT_RIGHT])
        m_object->setVelocityX(1);
    if (m_inputs[INPUT_DOWN])
        m_object->setVelocityY(-1);
}