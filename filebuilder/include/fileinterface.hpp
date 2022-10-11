#pragma once

class FileInterface
{
protected:
    static constexpr const char SECT_ID         = char(-1);
    static constexpr const char SECT_START      = char(-2);
    static constexpr const char FIELD_ID        = char(-3);
    static constexpr const char FIELD_TYPE      = char(-4);
    static constexpr const char FIELD_STR       = char(-5);
    static constexpr const char FIELD_INT       = char(-6);
    static constexpr const char FIELD_UINT      = char(-7);
    static constexpr const char FIELD_ARR       = char(-8);
    static constexpr const char ARR_STR         = char(-9);
    static constexpr const char ARR_INT         = char(-10);
    static constexpr const char ARR_UINT        = char(-11);
    static constexpr const char ARR_UCHAR       = char(-12);
    static constexpr const char ARR_BREAK       = char(-13);
};