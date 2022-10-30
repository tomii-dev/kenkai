#include "game.hpp"

#include "component/animator.hpp"
#include "object/entity/player.hpp"

std::unique_ptr<Game> Game::s_instance;

Game::Game() 
    : m_window(sf::VideoMode(1920, 1080), "kenkai")
    , m_world(m_window)
{}

/* static */ Game& Game::make()
{
    assert(!s_instance);

    s_instance = std::unique_ptr<Game>(new Game());
    return *s_instance.get();
}

int Game::run()
{
    Player* player = m_world.addObject<Player>();
    m_control.setObject(player);
    player->setPosition(100, 0);

    Entity* test = m_world.addObject<Entity>();
    test->setPosition(200, 0);

    sf::Clock deltaClock;

    while(m_window.isOpen())
    {
        pollEvents();
        update(deltaClock.restart());
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
            break;
        case sf::Event::KeyPressed:
            m_control.sendSfmlKey(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            m_control.sendSfmlKey(event.key.code, false);
            break;
        case sf::Event::MouseButtonPressed:
            m_control.mouseClick();
        }
    }
}

void Game::update(const sf::Time& delta)
{
    m_taskMgr.update(m_clock.getElapsedTime());
    m_control.update();
    m_world.update(delta);
}

void Game::render()
{
    m_window.clear(sf::Color::White);
    m_world.render();
    m_window.display();
}