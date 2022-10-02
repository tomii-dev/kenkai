#pragma once

#include "util/taskmanager.hpp"

#include <SFML/Graphics.hpp>
#include <memory>

class Game
{
public:
    static Game& make();
    static inline Game& get() { assert(s_instance); return *s_instance.get(); }

    Game(const Game&) = delete;
    Game(Game&&) = delete;

    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

    int run();

private:
    Game();

    void update();
    void render();

    static std::unique_ptr<Game> s_instance;

    sf::RenderWindow m_window;
    sf::Clock m_clock;

    TaskManager m_taskMgr;
};