#pragma once

#include "filewriter.hpp"

#include <string>

class Builder
{
public:
    inline Builder(const std::string& path) : m_writer(path) {}

    virtual void build() { m_writer.write(); }
protected:
    FileWriter m_writer;
};