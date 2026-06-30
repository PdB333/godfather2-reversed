// FUNC_NAME: Entity::isActive (bit0 of flags at +0x38)
// 0x005f67f0 – Returns true if the active flag (bit 0 of byte at +0x38) is set.
bool Entity::isActive() const {
    return (*(const uint8_t*)((uintptr_t)this + 0x38) & 1) != 0;
}