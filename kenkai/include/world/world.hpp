#pragma once

#include "object/object.hpp"

#include <vector>
#include <memory>
#include <SFML/System.hpp>

#include "room/room.hpp"
#include "room/home.hpp"

class World
{
public:
    World(sf::RenderWindow& window);

    void update(const sf::Time& delta);
    void render();
    
    template <typename ObjectType>
    ObjectType* addObject()
    {
        static_assert(std::is_base_of<Object, ObjectType>::value);

        m_objects.push_back(std::make_unique<ObjectType>());
        return dynamic_cast<ObjectType*>(m_objects.back().get());
    }
private:
    sf::RenderWindow& m_window;
    std::vector<std::unique_ptr<Object>> m_objects;

    Object m_ground;
    Object m_bg;

    std::unique_ptr<Home> m_home;
    Room* m_room;
    
    struct Stage
    {
        using RoomList = std::vector<std::unique_ptr<Room>>;
        RoomList rooms;

        void generate();
    } m_stage;

    void enter();
};