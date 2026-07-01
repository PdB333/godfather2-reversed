// FUNC_NAME: Entity::setVisibilityFlag
void __thiscall Entity::setVisibilityFlag(bool enable) {
    if (enable) {
        *(uint32_t *)(this + 0x37c) |= 0x8;  // +0x37c: flags field, bit 3 = visibility indicator
    } else {
        *(uint32_t *)(this + 0x37c) &= ~0x8;
    }
}