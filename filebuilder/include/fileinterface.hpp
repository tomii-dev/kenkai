#pragma once

#include <map>
#include <string>

class FileInterface
{
protected:

    // all separators are 3 chars long
    static constexpr const int SEP_SIZE = 3;

    static constexpr const char SECT_ID[]       = "?SI";
    static constexpr const char SECT_START[]    = "?SS";
    static constexpr const char SECT_END[]      = "?SE";
    static constexpr const char FIELD_ID[]      = "?FI";
    static constexpr const char FIELD_TYPE[]    = "?FT";
    static constexpr const char FIELD_END[]     = "?FE";
    static constexpr const char ARR_START[]     = "?AS";
    static constexpr const char ARR_BREAK[]     = "?AB";

    enum SeparatorType
    {
        SPTR_SECT_ID,
        SPTR_SECT_START,
        SPTR_SECT_END,
        SPTR_FIELD_ID,
        SPTR_FIELD_TYPE,
        SPTR_FIELD_END,
        SPTR_ARR_BREAK
    };

    const std::map<std::string, SeparatorType> m_separators = {
        {SECT_ID, SPTR_SECT_ID},
        {SECT_START, SPTR_SECT_START},
        {SECT_END, SPTR_SECT_END},
        {FIELD_ID, SPTR_FIELD_ID},
        {FIELD_TYPE, SPTR_FIELD_TYPE},
        {FIELD_END, SPTR_FIELD_END},
        {ARR_BREAK, SPTR_ARR_BREAK}
    };

    static constexpr const char FIELD_STR       = char(-1);
    static constexpr const char FIELD_INT       = char(-2);
    static constexpr const char FIELD_UINT      = char(-3);
    static constexpr const char FIELD_ARR       = char(-4);

    static constexpr const char ARR_STR         = char(-5);
    static constexpr const char ARR_INT         = char(-6);
    static constexpr const char ARR_UINT        = char(-7);
    static constexpr const char ARR_UCHAR       = char(-8);
};