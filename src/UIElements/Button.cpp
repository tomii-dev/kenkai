#include "UIElements/Button.hpp"
#include "Tools.hpp"
#include "Properties.hpp"
#include <iostream>

Button::Button(){
    Setup();
}

Button::Button(const std::string& text, ButtonSize size)
    : m_text(text), m_size(size)
{
    Setup();
}

Button::Button(ButtonSize size) : m_size(size){
    Setup();
}

void Button::Setup(){
    switch(m_size){
    case small:
        sizeX, sizeY = 50, 20;
        break;
    case medium:
        sizeX, sizeY = 70, 40;
        break;
    case big:
        sizeX, sizeY = 100, 70;
        break;
    default:
        break;
    }
    setTexture("button.png");
    setPosition(Properties::screenCenter);
    name = "button";
}

void Button::Update(){
    sf::Vector2f mousePos = Tools::getMousePosition();
    if(Tools::InRange(mousePos, sprite.getPosition(), 50))
        std::cout << "woop" << std::endl;
}