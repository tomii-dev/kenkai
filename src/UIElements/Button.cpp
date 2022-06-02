#include "UIElements/Button.hpp"
#include "Tools.hpp"
#include "Game.hpp"
#include "Properties.hpp"
#include "Events.hpp"
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
    Events::HookTo(MousePressed, [this](){ m_mousePressed = true; });
}

void Button::Update(){
    sf::Vector2f mousePos = Tools::getMousePosition();
    if (Tools::InRange(mousePos, getCenter(), sf::Vector2f(m_sizeX, m_sizeY))){
        setTexture("button_darkened.png");
        if(m_mousePressed)
            std::cout << "clicked!";
    }
    else setTexture("button.png");
}