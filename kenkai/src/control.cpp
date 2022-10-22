#include "control.hpp"

#include "object/object.hpp"
#include "object/entity/entity.hpp"

void Control::sendSfmlKey(const sf::Keyboard::Key& key, bool pressed)
{
    if (!m_keyControls.count(key))
        return;

    doInput(m_keyControls[key], pressed);
}

void Control::doInput(const Input& input, bool pressed)
{
    switch (input)
    {
    case INPUT_JUMP:
    {
        if (Entity* ent = static_cast<Entity*>(m_object))
            ent->jump();
        break;
    }
    default:
        m_inputs[input] = pressed;
    }
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