#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#define BUTTON_COUNT 3

enum ButtonState { BUTTON_UP, BUTTON_DOWN };

enum Button
{
    BUTTON_MOVE_LEFT,
    BUTTON_MOVE_RIGHT,
    BUTTON_JUMP
};

typedef std::vector<ButtonState> ControlTable;

namespace control
{
    ButtonState getButtonState(Button btn);
    Button btnFromSfmlKey(sf::Keyboard::Key key);
    void updateTable(Button btn, ButtonState state);
}