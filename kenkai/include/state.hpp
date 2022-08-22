#pragma once

enum EntityState
{
    ENTITY_ONGROUND     = 0x01,
    ENTITY_INAIR        = 0x02,
    ENTITY_MOVINGLEFT   = 0x04,
    ENTITY_MOVINGRIGHT  = 0x08,
    ENTITY_JUMPING      = 0x10
};

inline EntityState operator |=(EntityState& left, EntityState right)
{
    return left = EntityState(left | right);
}