#include "builder/animationbuilder.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

void* AnimationBuilder::addAnimation(const std::string& id)
{
    m_animations.push_back(std::make_unique<Animation>(id));
    return m_animations.back().get();
}

void AnimationBuilder::addFrame(void* animation, uint32_t width, uint32_t height, PixelData pxData, size_t size, uint32_t duration)
{
    Animation* anim = (Animation*)animation;
    assert(anim);

    anim->frames.push_back({ width, height, pxData, size, duration });
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
    for (const std::unique_ptr<Animation>& anim : m_animations)
    {
        const std::string animId = "anim_" + anim->id;

        m_writer.beginSection(animId);
        m_writer.addUIntField("count", anim->frames.size());

        size_t ind = 0;
        for (const FrameData& frame : anim->frames)
        {
            const std::string frameId = "f" + std::to_string(ind) + "_";

            m_writer.addUIntField(frameId + "dur", frame.duration);
            m_writer.addUIntField(frameId + "w", frame.width);
            m_writer.addUIntField(frameId + "h", frame.height);
            m_writer.addArrField(frameId + "px", std::vector<uint8_t>(frame.pxData, frame.pxData + frame.size));
            ind++;
        }
    }

    m_writer.write();
}