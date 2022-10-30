#include "world/world.hpp"

#include "../../filebuilder/include/filereader.hpp"
#include "util/num.hpp"
#include "object/entity/entity.hpp"

const int g_groundHeight = -200;

World::World(sf::RenderWindow& window) 
    : m_window(window)
    , m_home(std::make_unique<Home>())
{
    m_home->onEnterKenkai()->add([this]() { enter(); });
    m_home->onEnterKenkai()->fire();
}

void World::update(const sf::Time& delta)
{
    if(m_room)
        m_room->update(delta);

    for (const std::unique_ptr<Object>& obj : m_objects)
    {
        obj->update(delta);

        const float grndPos = m_ground.worldPosition().y;
        const float objPos = obj->worldPosition().y;
        if (objPos > grndPos)
            obj->setVelocityY(-400);
        else
            if (Entity* ent = dynamic_cast<Entity*>(obj.get()))
                ent->canJump(true);
    }
}

void World::render()
{
    if(m_room)
        m_room->render(m_window);

    m_bg.render(m_window);
    m_ground.render(m_window);

    for (const std::unique_ptr<Object>& obj : m_objects)
        obj->render(m_window);
}

void World::enter()
{
    m_stage.generate();
    m_room = m_stage.rooms[0].get();

    m_ground = Object();
    m_ground.setTexture(m_room->groundImg());
    m_ground.setPosition(0, -m_room->groundY());

    m_bg = Object();
    m_bg.setTexture(m_room->bgImg());
}

void World::Stage::generate()
{
    for (uint8_t i = 0; i < 4; i++)
    {
        const int ind = num::random(0, Room::BIOME_COUNT);
        const Room::Biome biome = Room::BIOME_PLAINS;

        rooms.push_back(std::make_unique<Room>(biome));
    }
}