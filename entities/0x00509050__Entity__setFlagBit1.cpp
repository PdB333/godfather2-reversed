// FUNC_NAME: Entity::setFlagBit1
void __thiscall Entity::setFlagBit1(bool enable) {
    // +0x08: flags word (bit 1 = flag for this property)
    if (enable) {
        *(unsigned int*)((char*)this + 8) |= 2;   // Set bit 1
    } else {
        *(unsigned int*)((char*)this + 8) &= ~2;  // Clear bit 1
    }
}