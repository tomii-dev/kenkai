#pragma once

#include <SFML/Graphics.hpp>

#include "world.hpp"

struct Animation
{
    unsigned int nFrames;
    unsigned char** frames;
};

class Game
{
private:
    static Game* s_instance;
    sf::RenderWindow m_window;
    World m_world;
    unsigned int m_frame;
    void update();
    void render();
    void handleEvents();
public:
    Game();
    int run();
    static unsigned int getFrame();
};