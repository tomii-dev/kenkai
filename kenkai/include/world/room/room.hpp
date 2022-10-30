#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <map>

class Object;

class Room
{
public:
    inline int groundY() const { return m_groundY; }
    inline const sf::Image& groundImg() const { return m_groundImg; }
    inline const sf::Image& bgImg() const { return m_bgImg; }

    virtual bool isBossRoom() const { return false; }

    // some more advanced rooms (such as home) might need logic
    virtual void update(const sf::Time& delta) {}
    virtual void render(sf::RenderWindow& window) {}

    static constexpr const uint32_t BIOME_COUNT = 6;

    enum Biome
    {
        BIOME_NONE,
        BIOME_PLAINS,
        BIOME_DESERT,
        BIOME_DUNGEON,
        BIOME_FOREST,
        BIOME_JUNGLE,
        BIOME_VOID
    };

    inline const Biome& biome() const { return m_biome; }

    Room(Biome biome = BIOME_NONE);

private:
    int m_groundY;
    sf::Image m_groundImg;
    sf::Image m_bgImg;
    Biome m_biome;

    static const std::map<Biome, std::string> s_biomePaths;
};