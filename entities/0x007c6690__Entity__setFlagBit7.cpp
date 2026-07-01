// FUNC_NAME: Entity::setFlagBit7
void __thiscall Entity::setFlagBit7(bool value) {
    if (value) {
        *(uint*)(this + 0x128) |= 0x80;  // +0x128: flags bitfield
    } else {
        *(uint*)(this + 0x128) &= ~0x80; // clear bit 7
    }
}