#include "UIElements/Button.hpp"
#include "Tools.hpp"
#include "Game.hpp"
#include "Properties.hpp"
#include "Events.hpp"
#include <iostream>

Button::Button(){
    Setup();
}

Button::Button(const std::string& text, sf::Vector2f size, sf::Vector2f position, std::function<void()> f)
    : m_text(text)
{
    m_sizeX = position.x;
    m_sizeY = position.y;
    m_action = f;
    Setup();
}

Button::Button(const std::string& text, sf::Vector2f size, sf::Vector2f position)
    : m_text(text)
{
    m_sizeX = position.x;
    m_sizeY = position.y;
    Setup();
}

void Button::Setup(){
    name = "button";
    m_type = ElementType::Button;
    m_mousePressed = false;
    Events::HookTo(MousePressed, [this](){ m_mousePressed = true; });
    UIElement::Setup();
}

void Button::setAction(std::function<void()> f){
    m_action = f;
}

void Button::Update(){
    sf::Vector2f mousePos = Tools::getMousePosition();
    if (Tools::InRange(mousePos, getCenter(), sf::Vector2f(m_sizeX, m_sizeY))){
        setTexture("button_darkened.png");
        if(m_mousePressed){
            m_action();
            m_mousePressed = false;
        }
    }
    else setTexture("button.png");
}