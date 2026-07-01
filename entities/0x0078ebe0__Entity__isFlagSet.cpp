// FUNC_NAME: Entity::isFlagSet
bool __thiscall Entity::isFlagSet(byte flagBit) {
    // m_flags at offset +0x30: bitfield byte
    byte m_flags = *(byte *)(this + 0x30);
    if (m_flags == 0) {
        return true; // No flags set -> returns true for any bit
    }
    return (1 << (flagBit & 0x1f)) & m_flags;
}