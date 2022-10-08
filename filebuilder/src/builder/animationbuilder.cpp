#include "builder/animationbuilder.hpp"

void AnimationBuilder::addFrame(PixelData pxData, size_t size, uint32_t duration)
{
    m_frames.push_back({ pxData, size, duration });
}

/* static */ AnimationBuilder::PixelData AnimationBuilder::pxlDataFromFile(const std::string& path)
{

}

void AnimationBuilder::build()
{
    m_writer.beginSection("inf");
    m_writer.addUIntField("count", m_frames.size());

    size_t ind = 0;
    for (const FrameData& frame : m_frames)
    {
        m_writer.beginSection("f" + ind);
        m_writer.addUIntField("dur", frame.duration);
        m_writer.addArrField("px", std::vector<unsigned char>(frame.pxData, frame.pxData + frame.size));
    }

    m_writer.write();
}