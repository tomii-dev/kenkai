#pragma once

#include <string>
#pragma once

#include "fileinterface.hpp"

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>

class FileWriter : private FileInterface
{
public:
    inline FileWriter(const std::string& path) : m_path(path)
    {}

    void beginSection(const std::string& id);

    void addStrField(const std::string& id, const std::string& data);
    void addIntField(const std::string& id, const int& data);
    void addUIntField(const std::string& id, const uint32_t& data);

    template<typename ArrType>
    void addArrField(const std::string& id, const std::vector<ArrType> arr)    {
        const bool isStr = std::is_same<ArrType, std::string>::value;
        const bool isInt = std::is_same<ArrType, int>::value;
        const bool isUInt = std::is_same<ArrType, uint32_t>::value;
        const bool isUChar = std::is_same<ArrType, uint8_t>::value;

        static_assert(isStr || isInt || isUInt || isUChar);

        m_buf << FIELD_ID << id << FIELD_TYPE << FIELD_ARR;

        if (isStr) m_buf << ARR_STR;
        if (isInt) m_buf << ARR_INT;
        if (isUChar) m_buf << ARR_UCHAR;
        if (isUInt) m_buf << ARR_UINT;

        for (const ArrType& item : arr)
        {
            m_buf << item;

            // uchars don't need arr separators as they are one
            // character, this is helpful for img data, reduces file size
            if (!isUChar)
                m_buf << ARR_BREAK;
        }

        m_buf << FIELD_END;
    }
    
    void write();
private:
    std::string m_path;
    std::ofstream m_ofs;
    std::stringstream m_buf;

    uint32_t m_section = 0;

    void writeInt(int num);
    void writeUInt(uint32_t num);
};