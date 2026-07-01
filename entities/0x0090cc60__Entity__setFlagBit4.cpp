// FUNC_NAME: Entity::setFlagBit4
void __thiscall Entity::setFlagBit4(bool enable) {
    // +0x14: flags field (bit 4)
    if (enable) {
        *(uint32_t*)(this + 0x14) |= 0x10;
    } else {
        *(uint32_t*)(this + 0x14) &= ~0x10;
    }
}