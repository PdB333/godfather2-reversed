// Address: 0x00566a60
// Role: Setter for bit 2 in flags field at offset 0x2C. Enables/disables some boolean state.
// FUNC_NAME: Entity::setFlagBit2

void __thiscall Entity::setFlagBit2(bool enable)
{
    uint32_t* flags = reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x2C); // +0x2C flags field
    if (enable) {
        *flags |= 0x4;   // set bit 2
    } else {
        *flags &= ~0x4;  // clear bit 2
    }
}