#include "game.hpp"

Game::Game() {}

int Game::run()
{
    return 0;
}

/* static */ Game& Game::make()
{
    assert(!s_instance);

    s_instance = std::make_unique<Game>();
    return *s_instance;
}