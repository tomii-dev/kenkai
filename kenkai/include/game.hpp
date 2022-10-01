#pragma once

#include <memory>

class Game
{
public:
    static Game& make();
    static inline Game& get() { return *s_instance.get(); }

    Game(const Game&) = delete;
    Game(Game&&) = delete;

    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;
    int run();

private:
    Game();

    static std::unique_ptr<Game> s_instance;
};