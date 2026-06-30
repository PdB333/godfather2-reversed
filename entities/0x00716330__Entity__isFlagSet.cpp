// FUNC_NAME: Entity::isFlagSet
bool __thiscall Entity::isFlagSet(void) {
    // Check bit 0 at offset 0x308 (likely a boolean flag)
    return (*(volatile uint8_t*)((uintptr_t)this + 0x308) & 1) != 0;
}