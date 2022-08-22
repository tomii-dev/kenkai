#include "control.hpp"

#include <iostream>

ControlTable g_controlTable(BUTTON_COUNT);

ButtonState control::getButtonState(Button btn)
{
    return g_controlTable[btn];
}

Button control::btnFromSfmlKey(sf::Keyboard::Key key)
{
    switch(key)
    {
    case sf::Keyboard::A:
        return BUTTON_MOVE_LEFT;
    case sf::Keyboard::D:
        return BUTTON_MOVE_RIGHT;
    case sf::Keyboard::Space:
        return BUTTON_JUMP;
    }
}

void control::updateTable(Button btn, ButtonState state)
{
    g_controlTable[btn] = state;
}