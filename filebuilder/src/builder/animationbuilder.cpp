#include "builder/animationbuilder.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

void AnimationBuilder::addFrame(PixelData pxData, size_t size, uint32_t duration)
{
    m_frames.push_back({ pxData, size, duration });
}

AnimationBuilder::ImagePixelData AnimationBuilder::pxlDataFromFile(const std::string& path)
{
    int width, height, channels;
    PixelData img = stbi_load(path.c_str(), &width, &height, &channels, 0);

    const size_t size = width * height * channels;

    m_imgs.push_back(std::unique_ptr<unsigned char>(img));
    return { m_imgs.back().get(), size };
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
        m_writer.addArrField("px", std::vector<unsigned char>(frame.pxData, frame.pxData + frame.size));
        ind++;
    }

    m_writer.write();
}