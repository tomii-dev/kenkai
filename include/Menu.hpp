# pragma once

#include "SFML/Graphics.hpp"
#include "UIElement.hpp"
#include <vector>

class Menu{
    sf::RenderWindow& m_window;
    std::vector<UIElement*> m_elements;
protected:
    void AddElement(UIElement element);
    void AddElement(UIElement* element);
public:
    Menu(sf::RenderWindow& window);
    ~Menu();
    void Render();
};