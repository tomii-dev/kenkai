#pragma once

#include "filewriter.hpp"

#include <string>
#include <vector>
#include <memory>

class AnimationBuilder
{
public:
    inline AnimationBuilder(const std::string& path) : m_writer(path)
    {}

    using PixelData = uint8_t*;
    
    void* addAnimation(const std::string& id);

    void addFrame(void* anim, uint32_t width, uint32_t height, PixelData pxData, size_t size, uint32_t duration);

    struct ImagePixelData
    {
        int width;
        int height;
        PixelData data;
        size_t size;
    };

    ImagePixelData pxlDataFromFile(const std::string& path);

    void build();
private:
    struct FrameData
    {
        uint32_t width;
        uint32_t height;
        PixelData pxData;
        size_t size;
        uint32_t duration; // in ms
    };

    struct Animation
    {
        std::string id;
        std::vector<FrameData> frames;

        inline Animation(const std::string& _id) : id(_id) {}
    };

    std::vector<std::unique_ptr<Animation>> m_animations;
    FileWriter m_writer;

    // AnimationBuilder needs to own all dynamically allocated img arrays given by 
    // pxlDataFromFile so it can clean them up on destruction
    std::vector<std::unique_ptr<uint8_t>> m_imgs;
};