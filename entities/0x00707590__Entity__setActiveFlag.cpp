// FUNC_NAME: Entity::setActiveFlag
// Address: 0x00707590
// Sets or clears bit 6 (0x40) of the flags field at offset +0x1d0 based on the boolean parameter.

void __thiscall Entity::setActiveFlag(bool isActive) {
    if (isActive) {
        *(uint *)(this + 0x1d0) |= 0x40;
    } else {
        *(uint *)(this + 0x1d0) &= ~0x40;
    }
}