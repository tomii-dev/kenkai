#include "filereader.hpp"

#include <iostream>
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
        STATE_ARR_TYPE,     // Reading array type
        STATE_FIELD         // Reading field data
    } readerState;

    // one of the field types defined by file format
    // (see fileinterface.hpp)
    char fieldType;

    // if the field is of an array type, we need to store
    // the type of the data it holds, these are also given by
    // a char (see fileinterface.hpp)
    char arrType = ' ';

    // store the current index we are writing to in the array
    // helpful for str arrays
    int32_t ind = 0;

    for (int i = 0; i < length; i++)
    {
        switch (input[i])
        {
        case SECT_ID:
        {
            if (currentSection.id.size())
            {
                m_sections.push_back(currentSection);
                currentSection = Section();
            }
            readerState = STATE_SECT_ID;
            continue;
        }
        case SECT_START:
            readerState = STATE_SECT_START;
            continue;
        case FIELD_ID:
        {
            if (currentField.id.size())
            {
                currentSection.fields.push_back(currentField);
                currentField = Field();
            }
            readerState = STATE_FIELD_ID;
            continue;
        }
        case FIELD_TYPE:
            readerState = STATE_FIELD_TYPE;
            continue;
        case ARR_BREAK:
            ind++;
            continue;
        }
        
        switch (readerState)
        {
        case STATE_SECT_ID:
            currentSection.id += input[i];
            continue;
        case STATE_FIELD_ID:
            currentField.id += input[i];
            continue;
        case STATE_FIELD_TYPE:
        {
            fieldType = input[i];
            if (fieldType == FIELD_ARR)
            {
                ind = 0;
                readerState = STATE_ARR_TYPE;
                continue;
            }
            readerState = STATE_FIELD;
            continue;
        }
        case STATE_ARR_TYPE:
        {
            arrType = input[i];
            readerState = STATE_FIELD;
            continue;
        }
        }

        // state is STATE_FIELD, we are reading data
        switch (fieldType)
        {
        case FIELD_STR:
        {
            std::string& str = std::get<std::string>(currentField.data);
            str += input[i];
            break;
        }
        case FIELD_INT:
            currentField.data = (int)input[i];
            break;
        case FIELD_UINT:
            currentField.data = (uint32_t)input[i];
            break;
        case FIELD_ARR:
        {
            if (arrType == ARR_STR)
            {
                Arr<std::string>& arr = std::get<Arr<std::string>>(currentField.data);

                if (arr.size() - 1 < ind)
                    arr.push_back(std::string());

                arr.back() += input[i];

            }
            if (arrType == ARR_INT)
            {
                Arr<int>& arr = std::get<Arr<int>>(currentField.data);
                arr.push_back((int)input[i]);
            }
            if (arrType == ARR_UINT)
            {
                Arr<uint32_t> arr = std::get<Arr<uint32_t>>(currentField.data);
                arr.push_back((uint32_t)input[i]);
            }
            if (arrType == ARR_UCHAR)
            {
                Arr<unsigned char>& arr = std::get<Arr<unsigned char>>(currentField.data);
                arr.push_back((unsigned char)input[i]);
            }
            break;
        }
        }
    }
}