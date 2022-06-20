#include "UIElements/Button.hpp"
#include "Tools.hpp"
#include "Properties.hpp"
#include "Events.hpp"
#include "Assets.hpp"
#include <iostream>

Button::Button(){
    Setup();
}

Button::Button(const std::string& text, sf::Vector2f size, sf::Vector2f position, EventId event)
    : UIElement     (size.x, size.y, position),
      m_action      (event),
      m_text        (text, Assets::dosis)
{
    Setup();
}

Button::Button(const std::string& text, sf::Vector2f size, sf::Vector2f position)
    : UIElement (size.x, size.y, position),
    m_text      (text, Assets::dosis)
{
    Setup();
}

void Button::Setup(){
    name = "button";
    m_type = ElementType::Button;
    m_mousePressed = false;
    Events::HookTo(MousePressed, [this](){ m_mousePressed = true; });
    UIElement::Setup();
    m_text.setPosition(getCenter());
}

void Button::Update(){
    sf::Vector2f mousePos = Tools::getMousePosition();
    if (Tools::InRange(mousePos, getCenter(), sf::Vector2f(m_sizeX, m_sizeY))){
        setTexture("button_darkened.png");
        if(m_mousePressed){
            Events::Fire(m_action);
            m_mousePressed = false;
        }
    }
    else setTexture("button.png");
}

void Button::DrawTo(sf::RenderWindow* window){
    if(!visible)
        return;
    window->draw(sprite);
    window->draw(m_text);
}