#pragma once

#include "fileinterface.hpp"

#include <string>
#include <vector>
#include <variant>
#include <memory>
#include <algorithm>

class FileReader : private FileInterface
{
public:
    FileReader(const std::string& path);

    template<typename T>
    using Arr = std::vector<T>;

    using FieldData = std::variant<std::string, uint32_t, int,
        Arr<std::string>, Arr<int>, Arr<uint32_t>, Arr<unsigned char>>;

    template <typename FieldType>
    const FieldType& getField(const std::string& sectionId, const std::string& id)
    {
        const Section& section = *std::find_if(m_sections.begin(), m_sections.end(),
            [sectionId](const Section& s) { return s.id == sectionId; });

        return std::get<FieldType>(std::find_if(section.fields.begin(), section.fields.end(),
            [id](const Field& field) { return field.id == id; })->data);
    }
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