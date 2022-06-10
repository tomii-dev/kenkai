#include "Menu.hpp"
#include <fstream>

#include "SFML/Graphics.hpp"

Menu::Menu() : m_window(nullptr)
{}

Menu::Menu(sf::RenderWindow* window, const std::vector<UIElement> elements)
    : m_window(window),
    m_elements(elements),
    m_cursor(20, 20)
{}

Menu::Menu(sf::RenderWindow* window, const std::string& id)
    : m_window(window),
    m_cursor  (20, 20)
{
    m_elements.push_back(m_cursor);
    load(id);
}

Menu::~Menu(){
}

void Menu::load(const std::string& id){
    std::ifstream ifs(MENU_PATH + id + ".dat", std::ios::binary);
    boost::archive::binary_iarchive iarch(ifs);
    MenuConfig conf;
    iarch >> conf;
    std::vector<UIElement> temp;
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
            case ElementType::Button:
                m_elements.push_back(Button("", size, position));
                break;
        }
        ++i;
    }
    Menu(m_window, temp);
}

void Menu::Render(){
    for (UIElement e : m_elements) {
        e.Update();
        e.DrawTo(m_window);
    }
}

void Menu::AddElement(UIElement element){
    m_elements.push_back(element);
}