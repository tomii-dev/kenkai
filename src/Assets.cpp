#include "Assets.hpp"

sf::Font Assets::dosis;

void Assets::initAssets(){
    dosis.loadFromFile("assets/fonts/dosis.ttf");
}