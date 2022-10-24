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

    using FieldData = std::variant<std::monostate, std::string, uint32_t, int,
        Arr<std::string>, Arr<int>, Arr<uint32_t>, Arr<uint8_t>>;

    const Arr<std::string> sections() const;

    template <typename FieldType>
    const FieldType& getField(const std::string& sectionId, const std::string& id)
    {
        const Arr<Section>::iterator secIt = std::find_if(m_sections.begin(), m_sections.end(),
            [sectionId](const Section& s) { return s.id == sectionId; });

        if (secIt == m_sections.end())
            return FieldType();
        
        const Arr<Field>::iterator fieldIt = std::find_if(secIt->fields.begin(), secIt->fields.end(),
            [id](const Field& field) { return field.id == id; });

        if (fieldIt == secIt->fields.end())
            return FieldType();

        return std::get<FieldType>(fieldIt->data);
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

    size_t m_length;
    char* m_input;

    Arr<Section> m_sections;

    // check if current char in input starts separator
    // if so, write separator type to ref param
    bool isSeparator(int ind, SeparatorType& sep);
};