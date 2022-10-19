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

    using PixelData = unsigned char*;

    void addFrame(PixelData pxData, size_t size, uint32_t duration);

    struct ImagePixelData
    {
        PixelData data;
        size_t size;
    };

    ImagePixelData pxlDataFromFile(const std::string& path);

    void build();
private:
    struct FrameData
    {
        PixelData pxData;
        size_t size;
        uint32_t duration; // in ms
    };

    FileWriter m_writer;
    std::vector<FrameData> m_frames;

    // AnimationBuilder needs to own all dynamically allocated img arrays given by 
    // pxlDataFromFile so it can clean them up on destruction
    std::vector<std::unique_ptr<unsigned char>> m_imgs;
};