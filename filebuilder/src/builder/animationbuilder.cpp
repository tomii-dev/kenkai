#include "builder/animationbuilder.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

void AnimationBuilder::addFrame(uint32_t width, uint32_t height, PixelData pxData, size_t size, uint32_t duration)
{
    m_frames.push_back({ width, height, pxData, size, duration });
}

AnimationBuilder::ImagePixelData AnimationBuilder::pxlDataFromFile(const std::string& path)
{
    int width, height, channels;
    PixelData img = stbi_load(path.c_str(), &width, &height, &channels, 4);

    const size_t size = width * height * 4;

    m_imgs.push_back(std::unique_ptr<uint8_t>(img));
    return { width, height, m_imgs.back().get(), size };
}

void AnimationBuilder::build()
{
    m_writer.beginSection("inf");
    m_writer.addUIntField("count", m_frames.size());

    size_t ind = 0;
    for (const FrameData& frame : m_frames)
    {
        m_writer.beginSection("f" + std::to_string(ind));
        m_writer.addUIntField("dur", frame.duration);
        m_writer.addUIntField("w", frame.width);
        m_writer.addUIntField("h", frame.height);
        m_writer.addArrField("px", std::vector<uint8_t>(frame.pxData, frame.pxData + frame.size));
        ind++;
    }

    m_writer.write();
}