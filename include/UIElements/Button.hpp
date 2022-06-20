#pragma once

#include "UIElement.hpp"
#include "Events.hpp"
#include <string>
#include <functional>

class Button : public UIElement{
    sf::Text m_text;
    bool m_mousePressed;
    EventId m_action;
    void Setup() override;
public:
    Button();
    Button(const std::string& text, sf::Vector2f size, sf::Vector2f position);
    Button(const std::string& text, sf::Vector2f size, sf::Vector2f position, EventId event);
    void Update() override;
    void DrawTo(sf::RenderWindow* window) override;
};