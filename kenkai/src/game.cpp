#include "game.hpp"

std::unique_ptr<Game> Game::s_instance;

Game::Game() : m_window(sf::VideoMode(800, 600), "kenkai")
{}

/* static */ Game& Game::make()
{
    assert(!s_instance);

    s_instance = std::unique_ptr<Game>(new Game());
    return *s_instance.get();
}

int Game::run()
{
    while(m_window.isOpen())
    {
        pollEvents();
        update();
        render();
    }

    return 0;
}

void Game::pollEvents()
{
    sf::Event event;
    while(m_window.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            m_window.close();
        }
    }
}

void Game::update()
{
    m_taskMgr.update(m_clock.getElapsedTime());
}

void Game::render()
{
    m_window.clear(sf::Color::White);
    m_window.display();
}