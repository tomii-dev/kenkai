#include "builder/animationbuilder.hpp"

#include <assert.h>

void* AnimationBuilder::addAnimation(const std::string& id)
{
    m_animations.push_back(std::make_unique<Animation>(id));
    return m_animations.back().get();
}

void AnimationBuilder::addFrame(void* animation, uint32_t width, uint32_t height, img::PixelData pxData, size_t size, uint32_t duration)
{
    Animation* anim = (Animation*)animation;
    assert(anim);

    anim->frames.push_back({ width, height, pxData, size, duration });
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

    Builder::build();
}