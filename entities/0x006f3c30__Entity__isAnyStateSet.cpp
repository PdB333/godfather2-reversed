// FUNC_NAME: Entity::isAnyStateSet
// Function address: 0x006f3c30
// Checks if any of four boolean flags (at offsets +0x40, +0x74, +0xa8, +0xdc) are set.
// Returns 1 (true) if at least one flag is non-zero; otherwise returns 0 (false).
bool __thiscall Entity::isAnyStateSet(void) {
    // Offsets correspond to state flags: e.g., isDead (+0x40), isStunned (+0x74), etc.
    if (*(char*)((int)this + 0xDC) == 0 &&
        *(char*)((int)this + 0xA8) == 0 &&
        *(char*)((int)this + 0x74) == 0 &&
        *(char*)((int)this + 0x40) == 0) {
        return false;
    }
    return true;
}