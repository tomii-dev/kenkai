#include "entities/player.hpp"

#include "control.hpp"

Player::Player(const char* name, World* world) : Entity("player", world) 
{
    setTexture("player.png");
}

void Player::update(int deltaTime)
{   
    // change velocity depending on controls
    if (control::getButtonState(BUTTON_MOVE_LEFT))
        m_velocity.x = -1;
    else if(control::getButtonState(BUTTON_MOVE_RIGHT))
        m_velocity.x = 1;
    else m_velocity.x = 0;

    if(control::getButtonState(BUTTON_JUMP))
        jump(deltaTime);

    Entity::update(deltaTime);
}