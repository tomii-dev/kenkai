# pragma once

#include "SFML/Graphics.hpp"
#include "UIElement.hpp"
#include "UIElements/Cursor.hpp"
#include "UIElements/Button.hpp"
#include <vector>
#include <string>
#include <boost/variant.hpp>
#include <boost/serialization/variant.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#define MENU_PATH "assets/data/menus/"

using namespace boost;
typedef variant<float, std::string, int> ArgValue;
typedef std::map<std::string, ArgValue> UIElementArgs;

enum class MenuId{
    Main,
};

struct MenuConfig{
    std::vector<int> elements;
    std::vector<UIElementArgs> elementArgs;
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& elements;
        ar& elementArgs;
    }
};

class Menu{
    sf::RenderWindow* m_window;
    std::vector<UIElement*> m_elements;
    Cursor* m_cursor;
    void load(MenuId id);
    Menu(sf::RenderWindow* window, const std::vector<UIElement*> elements);
public:
    Menu();
    Menu(sf::RenderWindow* window, MenuId id);
    ~Menu();
    void Render();
};