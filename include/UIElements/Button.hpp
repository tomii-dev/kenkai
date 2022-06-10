#pragma once

#include "UIElement.hpp"
#include <string>
#include <functional>

class Button : public UIElement{
    std::string m_text;
    bool m_mousePressed;
    std::function<void()> m_action;
    void Setup() override;
public:
    Button();
    Button(const std::string& text, sf::Vector2f size, sf::Vector2f position);
    Button(const std::string& text, sf::Vector2f size, sf::Vector2f position, std::function<void()> f);
    void Update() override;
    void setAction(std::function<void()> f);
};