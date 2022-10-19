#include "filereader.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>

FileReader::FileReader(const std::string& path)
{
    std::ifstream ifs(path, std::ios::in | std::ios::binary);
    if (ifs.fail())
        return;

    ifs.seekg(0, ifs.end);
    m_length = ifs.tellg();
    ifs.seekg(0, ifs.beg);
     
    m_input = new char[m_length];
    ifs.read(m_input, m_length);

    Section currentSection;
    Field currentField;
    
    enum ReaderState 
    { 
        STATE_SECT_ID,      // Currently reading section id
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
    uint32_t ind = 0;

    for (int i = 0; i < m_length; i++)
    {
        SeparatorType sep;
        if (isSeparator(i, sep))
        {
            switch (sep)
            {
            case SPTR_SECT_ID:
                readerState = STATE_SECT_ID;
                break;
            case SPTR_SECT_START:
                break;
            case SPTR_SECT_END:
            {
                m_sections.push_back(currentSection);
                currentSection = Section();
                break;
            }
            case SPTR_FIELD_ID:
            {
                readerState = STATE_FIELD_ID;
                break;
            }
            case SPTR_FIELD_TYPE:
                readerState = STATE_FIELD_TYPE;
                break;
            case SPTR_FIELD_END:
            {
                currentSection.fields.push_back(currentField);
                currentField = Field();
                break;
            }
            case SPTR_ARR_BREAK:
                ind++;
                break;
            }

            // skip past separator
            i += SEP_SIZE -  1;
            continue;
        }
        
        switch (readerState)
        {
        case STATE_SECT_ID:
            currentSection.id += m_input[i];
            continue;
        case STATE_FIELD_ID:
            currentField.id += m_input[i];
            continue;
        case STATE_FIELD_TYPE:
        {
            fieldType = m_input[i];
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
            arrType = m_input[i];
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
            str += m_input[i];
            break;
        }
        case FIELD_INT:
            currentField.data = (int)m_input[i];
            break;
        case FIELD_UINT:
            currentField.data = (uint32_t)m_input[i];
            break;
        case FIELD_ARR:
        {
            if (arrType == ARR_STR)
            {
                if (!currentField.data.index())
                    currentField.data = Arr<std::string>();

                Arr<std::string>& arr = std::get<Arr<std::string>>(currentField.data);

                if (arr.size() - 1 < ind)
                    arr.push_back(std::string());

                arr.back() += m_input[i];

            }
            if (arrType == ARR_INT)
            {
                if (!currentField.data.index())
                    currentField.data = Arr<int>();

                Arr<int>& arr = std::get<Arr<int>>(currentField.data);
                arr.push_back((int)m_input[i]);
            }
            if (arrType == ARR_UINT)
            {
                if (!currentField.data.index())
                    currentField.data = Arr<uint32_t>();

                Arr<uint32_t> arr = std::get<Arr<uint32_t>>(currentField.data);
                arr.push_back((uint32_t)m_input[i]);
            }
            if (arrType == ARR_UCHAR)
            {
                if (!currentField.data.index())
                    currentField.data = Arr<unsigned char>();

                Arr<unsigned char>& arr = std::get<Arr<unsigned char>>(currentField.data);
                arr.push_back((unsigned char)m_input[i]);
            }
            break;
        }
        }
    }
}

bool FileReader::isSeparator(int ind, SeparatorType& out)
{
    if (m_input[ind] != '?')
        return false;

    std::string sep;
    for (int i = 0; i < SEP_SIZE; i++)
        sep += m_input[ind + i];

    if (m_separators.find(sep) == m_separators.end())
        return false;

    out = m_separators.at(sep);
    return true;
}