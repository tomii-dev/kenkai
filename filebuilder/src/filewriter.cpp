#include "filewriter.hpp"

void FileWriter::beginSection(const std::string& id)
{
    if (m_section > 0)
        m_buf << SECT_END;

    m_buf << SECT_ID << id << SECT_START;

    m_section++;
}

void FileWriter::addStrField(const std::string& id, const std::string& data)
{
    m_buf << FIELD_ID << id << FIELD_TYPE << FIELD_STR << data << FIELD_END;
}

void FileWriter::addIntField(const std::string& id, const int& data)
{
    m_buf << FIELD_ID << id << FIELD_TYPE << FIELD_INT << data << FIELD_END;
}

void FileWriter::addUIntField(const std::string& id, const uint32_t& data)
{
    m_buf << FIELD_ID << id << FIELD_TYPE << FIELD_UINT;
    writeUInt(data);
    m_buf << FIELD_END;
}

void FileWriter::write()
{
    m_buf << SECT_END;

    m_ofs.open(m_path, std::ios::out | std::ios::binary);
    m_ofs << m_buf.str();
    m_ofs.close();
}

void FileWriter::writeInt(int num)
{

}

void FileWriter::writeUInt(uint32_t num)
{
    while (num > 0)
    {
        if (num > 127)
        {
            m_buf << (char)127;
            num -= 127;
            continue;
        }

        m_buf << (char)num;
        num = 0;
    }
}