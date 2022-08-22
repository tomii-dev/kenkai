#include "game.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

#include "event.hpp"
#include "control.hpp"
#include "entities/player.hpp"

Game* Game::s_instance = nullptr;

Game::Game() 
    : m_window  (sf::VideoMode(800, 600), "kenkai"),
      m_frame   (0)
{
    s_instance = this;
}

void Game::update()
{
    m_world.update();
}

void Game::render()
{
    m_window.clear(sf::Color::Blue);
    m_world.render(m_window);
    m_window.display();
}

void Game::handleEvents()
{
    sf::Event e;
    while(m_window.pollEvent(e))
    {
        switch(e.type)
        {
        case sf::Event::Closed: 
        {
            m_window.close();
            break;
        }
        case sf::Event::KeyPressed:
        {
            const Button btn(control::btnFromSfmlKey(e.key.code));
            control::updateTable(btn, BUTTON_DOWN);
            break;
        }
        case sf::Event::KeyReleased:
        {
            const Button btn(control::btnFromSfmlKey(e.key.code));
            control::updateTable(btn, BUTTON_UP);
            break;
        }
        }
    }
}

int Game::run()
{
    m_world.addEntity<Player>();
    while(m_window.isOpen())
    {
        handleEvents();
        update();
        render();
        
        m_frame++;
    }

    return 0;
}

unsigned int Game::getFrame()
{
    return s_instance->m_frame;
}