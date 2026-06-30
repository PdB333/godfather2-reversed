// FUNC_NAME: Entity::initFlags
// Address: 0x0071bfd0
// Sets initialization flags at offset +0x3c. If bit 0 is clear, sets bits 0 and 4.
// This is likely called to confirm an object's flags are in an active/initialized state.

void Entity::initFlags()
{
    // Flags at +0x3c (uint16): bit0 = initialized, bit4 = active (or similar)
    uint16_t* flags = reinterpret_cast<uint16_t*>(this + 0x3c);

    // Only set if the low byte's bit0 is not already set
    if ((*reinterpret_cast<uint8_t*>(flags) & 1) == 0)
    {
        *flags |= 1;        // Set bit 0 (initialized)
        *flags |= 0x10;     // Set bit 4 (active)
    }
}