#pragma once

#include "fileinterface.hpp"

#include <string>
#include <vector>
#include <variant>
#include <memory>

class FileReader : private FileInterface
{
public:
    FileReader(const std::string& path);

    template<typename T>
    using Arr = std::vector<T>;

    using FieldData = std::variant<std::string, uint32_t, int,
        Arr<std::string>, Arr<int>, Arr<uint32_t>>;

    const FieldData& getField(const std::string& sectionId, const std::string& id);
private:
    struct Field
    {
        std::string id;
        FieldData data;
    };

    struct Section
    {
        std::string id;
        Arr<Field> fields;
    };

    Arr<Section> m_sections;
};