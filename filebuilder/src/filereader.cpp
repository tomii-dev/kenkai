#include "filereader.hpp"

#include <fstream>
#include <algorithm>

FileReader::FileReader(const std::string& path)
{
    std::ifstream ifs(path);
    if (ifs.fail())
        return;

    ifs.seekg(0, ifs.end);
    int length = ifs.tellg();
    ifs.seekg(0, ifs.beg);

    char* input = new char[length];
    ifs.read(input, length);

    Section currentSection;
    Field currentField;
    
    enum ReaderState 
    { 
        STATE_SECT_ID,      // Currently reading section id
        STATE_SECT_START,   // Sector has begun
        STATE_FIELD_ID,     // Reading field id
        STATE_FIELD_TYPE,   // Reading field type
        STATE_FIELD         // Reading field data
    } readerState;

    // one of the field types defined by file format
    // (see fileinterface.hpp)
    char fieldType;

    // if the field is of an array type, we need to store
    // the type of the data it holds, these are also given by
    // a char (see fileinterface.hpp)
    char arrType;

    // because our file is read as a char array, fields
    // that contain arrays of strings need to have each char
    // between array breaks added to a string that is then
    // added to an array, so we need to store a string buffer to append the chars to
    std::string strBuf;

    for (int i = 0; i < length; i++)
    {
        switch (input[i])
        {
        case SECT_ID:
            readerState = STATE_SECT_ID;
            break;
        default: 
        {
            if (readerState == STATE_SECT_ID)
            {
                currentSection.id += input[i];
                break;
            }
            if (readerState == STATE_FIELD_ID)
            {
                currentField.id += input[i];
                break;
            }
            if (readerState == STATE_FIELD_TYPE)
            {
                fieldType = input[i];
                break;
            }

            // state is STATE_FIELD, we are reading data
            // nested switch....... um
            switch (fieldType)
            {
            case FIELD_STR:
                std::string& str = std::get<std::string>(currentField.data);
                str += input[i];
                break;
            case FIELD_INT:
                currentField.data = (int)input[i];
                break;
            case FIELD_UINT:
                currentField.data = (uint32_t)input[i];
                break;
            case FIELD_ARR:
            {
                if (arrType = ARR_STR)
                {
                    Arr<std::string>& arr = std::get<Arr<std::string>>(currentField.data);
                    arr.
                }
            }
            }

        }
        }
    }
}

const FileReader::FieldData& FileReader::getField(const std::string& sectionId, const std::string& id)
{
    const Section& section = *std::find_if(m_sections.begin(), m_sections.end(),
        [sectionId](const Section& s) { return s.id == sectionId; });

    return std::find_if(section.fields.begin(), section.fields.end(),
        [id](const Field& field) { return field.id == id; })->data;
}