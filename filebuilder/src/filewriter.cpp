#include "filewriter.hpp"

void FileWriter::beginSection(const std::string& id)
{
    if (m_section > -1)
        m_buf << SECT_END;

    m_buf << SECT_ID << id << SECT_START;
    m_section++;
}

void FileWriter::addStrField(const std::string& id, const std::string& data)
{
    m_buf << FIELD_ID << id << FIELD_TYPE << FIELD_STR << data;
}

void FileWriter::addIntField(const std::string& id, const int& data)
{
    m_buf << FIELD_ID << id << FIELD_TYPE << FIELD_INT << data;
}

void FileWriter::addUIntField(const std::string& id, const uint32_t& data)
{
    m_buf << FIELD_ID << id << FIELD_TYPE << FIELD_UINT << data;
}

void FileWriter::write()
{
    m_ofs.open(m_path, std::ios::out);
    m_ofs << m_buf.str();
    m_ofs.close();
}