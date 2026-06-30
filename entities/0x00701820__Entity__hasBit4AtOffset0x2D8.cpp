// FUNC_NAME: Entity::hasBit4AtOffset0x2D8
// Function address: 0x00701820
// Role: Checks if bit 4 of a DWORD at offset 0x2D8 is set, likely a flag field.
bool Entity::hasFlag4() const
{
    // Read flag word at +0x2D8, test bit 4 (0x10)
    return (*(uint32_t*)((uint8_t*)this + 0x2D8) >> 4) & 1;
}