// FUNC_NAME: Entity::setUpdateFlag (hypothesized based on flags and offsets)
void __fastcall Entity::setUpdateFlag(Entity* this) {
    // Set flag 0x800 at offset +0x5c (likely a dirty/needs update flag)
    *(uint32_t*)((uint8_t*)this + 0x5c) |= 0x800;

    // Pointer to a “manager” object at offset +0x9c (could be null or sentinel 0x48)
    int* managerPtr = *(int**)((uint8_t*)this + 0x9c);

    if (managerPtr != nullptr && managerPtr != (int*)0x48) {
        // Set flag 0x80000000 at offset +0x1f14 of the manager (e.g., notify manager of change)
        *(uint32_t*)((uint8_t*)managerPtr + 0x1f14) |= 0x80000000;
    } else if (managerPtr == nullptr) {
        // Global fallback flag at 0x1f5c (likely a singleton manager's pending flag)
        *(uint32_t*)0x1f5c |= 0x80000000;
    }
}