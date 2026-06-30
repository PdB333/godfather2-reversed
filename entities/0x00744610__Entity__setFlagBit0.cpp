// FUNC_NAME: Entity::setFlagBit0
// Address: 0x00744610
// Sets or clears bit 0 of the flags field at offset +0xA8.
// If enable is non-zero, the bit is set; otherwise, it is cleared.
void __thiscall Entity::setFlagBit0(bool enable)
{
    // Offset +0xA8: bitfield flags (uint32)
    uint* flags = reinterpret_cast<uint*>(reinterpret_cast<char*>(this) + 0xA8);
    if (enable) {
        *flags |= 1;          // Set bit 0
    } else {
        *flags &= ~1;         // Clear bit 0
    }
}