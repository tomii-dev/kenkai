#pragma once

#include "util/taskmanager.hpp"
#include "world/world.hpp"
#include "control.hpp"

#include <SFML/Graphics.hpp>
#include <memory>
#include <cassert>

class Game
{
public:
    static Game& make();
    static inline Game& get() { assert(s_instance); return *s_instance.get(); }

    Game(const Game&) = delete;
    Game(Game&&) = delete;

    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

    inline TaskManager& taskManager() { return m_taskMgr; }

    int run();

private:
    Game();

    void pollEvents();
    void update(const sf::Time& delta);
    void render();

    static std::unique_ptr<Game> s_instance;

    sf::RenderWindow m_window;
    sf::Clock m_clock;

    World m_world;
    TaskManager m_taskMgr;
    Control m_control;
};