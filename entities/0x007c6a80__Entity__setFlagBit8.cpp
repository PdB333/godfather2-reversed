// FUNC_NAME: Entity::setFlagBit8
void __thiscall Entity::setFlagBit8(bool value) {
    // Flags field at +0x128: bit 0x100 is toggled based on value
    if (value) {
        *(uint*)(this + 0x128) |= 0x100;
    } else {
        *(uint*)(this + 0x128) &= ~0x100;
    }
}