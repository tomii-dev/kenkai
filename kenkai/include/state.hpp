#pragma once

enum State
{
    OBJECT_ONGROUND     = 0x01,
    OBJECT_INAIR        = 0x02,
    OBJECT_MOVINGLEFT   = 0x04,
    OBJECT_MOVINGRIGHT  = 0x08,

    ENTITY_ONGROUND     = OBJECT_ONGROUND,
    ENTITY_INAIR        = OBJECT_INAIR,
    ENTITY_MOVINGLEFT   = OBJECT_MOVINGLEFT,
    ENTITY_MOVINGRIGHT  = OBJECT_MOVINGRIGHT,
    ENTITY_JUMPING      = 0x10,

};

inline State operator |=(State& left, State right)
{
    return left = State(left | right);
}