// FUNC_NAME: Entity::setActive
// Address: 0x00701830
// Sets the "active" flag (bit 4, 0x10) in the flags at offset +0x2d8.
void __thiscall Entity::setActive(bool enabled) {
    uint& flags = *(uint*)(this + 0x2d8); // +0x2d8: flags bitfield
    if (enabled) {
        flags |= 0x10;  // set bit 4 (active)
    } else {
        flags &= ~0x10; // clear bit 4 (active)
    }
}