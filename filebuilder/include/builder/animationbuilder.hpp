#pragma once

#include "filewriter.hpp"

#include <string>
#include <vector>

class AnimationBuilder
{
public:
    inline AnimationBuilder(const std::string& path) : m_writer(path)
    {}

    using PixelData = unsigned char*;

    void addFrame(PixelData pxData, size_t size, uint32_t duration);
    static PixelData pxlDataFromFile(const std::string& path);

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
};