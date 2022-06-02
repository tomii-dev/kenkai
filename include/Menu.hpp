# pragma once

#include "SFML/Graphics.hpp"
#include "UIElement.hpp"
#include "UIElements/Cursor.hpp"
#include <vector>

class Menu{
    sf::RenderWindow& m_window;
    std::vector<UIElement*> m_elements;
    Cursor m_cursor;
protected:
    void AddElement(UIElement* element);
public:
    Menu(sf::RenderWindow& window);
    ~Menu();
    void Render();
};