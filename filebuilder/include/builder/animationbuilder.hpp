#pragma once

#include "builder.hpp"

#include "image.hpp"

#include <string>
#include <vector>
#include <memory>

class AnimationBuilder : public Builder
{
public:
    inline AnimationBuilder(const std::string& path) : Builder(path)
    {}

    void* addAnimation(const std::string& id);

    void addFrame(void* anim, uint32_t width, uint32_t height, img::PixelData pxData, size_t size, uint32_t duration);

    void build() override;
private:
    struct FrameData
    {
        uint32_t width;
        uint32_t height;
        img::PixelData pxData;
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
};