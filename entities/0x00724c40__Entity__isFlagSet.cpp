// FUNC_NAME: Entity::isFlagSet
// Function at 0x00724c40: checks if a specific flag is set in the bitfield at offset 0x134.
bool __thiscall Entity::isFlagSet(uint flag) const {
    return (*(uint*)((uintptr_t)this + 0x134) & flag) != 0;
}