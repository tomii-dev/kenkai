#include "UIElements/Button.hpp"
#include "Tools.hpp"
#include "Game.hpp"
#include "Properties.hpp"
#include <iostream>

Button::Button(){
    Setup();
}

Button::Button(const std::string& text, float sizeX, float sizeY)
    : m_text(text)
{
    m_sizeX = sizeX;
    m_sizeY = sizeY;
    Setup();
}

Button::Button(float sizeX, float sizeY){
    m_sizeX = sizeX;
    m_sizeY = sizeY;
    Setup();
}

void Button::Setup(){
    setTexture("button.png");
    sf::Vector2f cent = sf::Vector2f(Game::getInstance().getWindow().getSize().x / 2.f, Game::getInstance().getWindow().getSize().y / 2.f);
    setPosition(cent);
}

void Button::Update(){
    sf::Vector2f mousePos = Tools::getMousePosition();
    if (Tools::InRange(mousePos, getCenter(), 100))
        setTexture("button_darkened.png");
    else setTexture("button.png");
}