#include "world/room/room.hpp"

#include "object/object.hpp"
#include "../../filebuilder/include/filereader.hpp"
#include "util/filesys.hpp"

const std::map<Room::Biome, std::string> Room::s_biomePaths = {
    {Room::BIOME_PLAINS, FileSys::roomPath() + "room_pln.ken"},
    {Room::BIOME_DESERT, FileSys::roomPath() + "room_des.ken"},
    {Room::BIOME_DUNGEON, FileSys::roomPath() + "room_dng.ken"},
    {Room::BIOME_FOREST, FileSys::roomPath() + "room_fst.ken"},
    {Room::BIOME_JUNGLE, FileSys::roomPath() + "room_jng.ken"},
    {Room::BIOME_VOID, FileSys::roomPath() + "room_vod.ken"}
};

Room::Room(Biome biome) : m_biome(biome)
{
    if (!biome)
        return;

    FileReader reader(s_biomePaths.at(biome));

    const uint32_t groundImgW = reader.getField<uint32_t>("grnd", "img_w");
    const uint32_t groundImgH = reader.getField<uint32_t>("grnd", "img_h");
    const std::vector<uint8_t> groundImgPx = reader.getField<std::vector<uint8_t>>("grnd", "img_px");

    const uint32_t bgImgW = reader.getField<uint32_t>("bg", "img_w");
    const uint32_t bgImgH = reader.getField<uint32_t>("bg", "img_h");
    const std::vector<uint8_t> bgImgPx = reader.getField<std::vector<uint8_t>>("bg", "img_px");

    m_groundY = reader.getField<uint32_t>("grnd", "y");

    m_groundImg.create(groundImgW, groundImgH, groundImgPx.data());
    m_bgImg.create(bgImgW, bgImgH, bgImgPx.data());
}