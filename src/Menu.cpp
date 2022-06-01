#include <iostream>
#include "Menu.hpp"

Menu::Menu(sf::RenderWindow& window)
    : m_window(window)
{}

Menu::~Menu(){
    std::vector<UIElement*>::iterator it;
    for(it = m_elements.end(); it != m_elements.begin(); it++){
        delete *it;
        m_elements.pop_back();
    }
}

void Menu::AddElement(UIElement element){
    m_elements.push_back(&element);
}

void Menu::AddElement(UIElement* element){
    m_elements.push_back(element);
}

void Menu::Render(){
    for(UIElement* e : m_elements)
        e->DrawTo(m_window);
}