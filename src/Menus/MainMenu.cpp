#include "Menus/MainMenu.hpp"
#include "UIElements/Button.hpp"

MainMenu::MainMenu(sf::RenderWindow& window)
    : Menu(window)
{
    AddElement(new Button(300.f, 119.f));
    
}