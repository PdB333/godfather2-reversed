// FUNC_NAME: Entity::setFlagBit8
void __thiscall Entity::setFlagBit8(char enable) {
    // Bit 8 (0x100) at offset +0x20 is a flag field (e.g., m_flags)
    if (enable != '\0') {
        *(uint32_t *)(this + 0x20) |= 0x100;
    } else {
        *(uint32_t *)(this + 0x20) &= ~0x100;
    }
}