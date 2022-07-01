#include "Menu.hpp"
#include <fstream>
#include <iostream>

#include "SFML/Graphics.hpp"

Menu::Menu() : m_window(nullptr)
{}

Menu::Menu(sf::RenderWindow* window, const std::vector<UIElement*> elements)
    : m_window(window),
    m_elements(elements),
    m_cursor(new Cursor(20, 20))
{}

Menu::Menu(sf::RenderWindow* window, MenuId id)
    : m_window(window),
    m_cursor  (new Cursor(20, 20))
{
    load(id);
}

Menu::~Menu(){
    std::cout << "destructor called!";
    std::vector<UIElement*>::iterator it;
    for(it = m_elements.begin(); it != m_elements.end();){
        delete *it;
        it = m_elements.erase(it);
    }
}

void Menu::load(MenuId id){
    std::ifstream ifs(MENU_PATH + std::to_string((int)id) + ".dat", std::ios::binary);
    boost::archive::binary_iarchive iarch(ifs);
    MenuConfig conf;
    iarch >> conf;
    std::vector<UIElement*> temp;
    int i = 0;
    for(int e : conf.elements){
        sf::Vector2f size(
            get<float>(conf.elementArgs[i]["sizeX"]),
            get<float>(conf.elementArgs[i]["sizeY"])
        );
        sf::Vector2f position(
            get<float>(conf.elementArgs[i]["posX"]),
            get<float>(conf.elementArgs[i]["posY"])
        );
        switch(ElementType(e)){
            case ElementType::Button:{
                EventId e = EventId(get<int>(conf.elementArgs[i]["action"]));
                m_elements.push_back(new Button("balls", size, position, e));
                break;
            }
        }
        ++i;
    }
    ifs.close();
    Menu(m_window, temp);
}

void Menu::Render(){
    for (UIElement* e : m_elements) {
        e->Update();
        e->DrawTo(m_window);
    }
    m_cursor->Update();
    m_cursor->DrawTo(m_window);
}