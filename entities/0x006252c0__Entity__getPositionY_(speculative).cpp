// FUNC_NAME: Entity::getPositionY (speculative)
// Function at 0x006252c0: Returns a float from offset 0x4 of an object (likely Y component of a position vector).
// This is a trivial getter, probably used frequently in physics or rendering.
float __thiscall Entity::getPositionY(void)
{
    // Read float at offset 4 relative to this (e.g., m_position.y)
    return *(float*)((int)this + 4);
}