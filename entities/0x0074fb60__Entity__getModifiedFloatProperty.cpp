// FUNC_NAME: Entity::getModifiedFloatProperty
// Function address: 0x0074fb60
// Retrieves a float property from offset +0x10c. If bit 4 of flags at +0x60 is set,
// the value is multiplied by the global multiplier at DAT_00d5c454.

float Entity::getModifiedFloatProperty() const
{
    float result = *(float *)((uintptr_t)this + 0x10C); // m_floatProperty
    if (*(uint32_t *)((uintptr_t)this + 0x60) & 0x10)   // m_flags bit 4
    {
        result *= *(float *)0x00d5c454; // g_globalMultiplier (likely a configurable constant)
    }
    return result;
}