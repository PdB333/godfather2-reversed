// FUNC_NAME: Entity::canUpdate
bool __fastcall Entity::canUpdate(Entity* this) {
    // Check if the entity's data flags have bit 17 (0x11) set.
    // If that bit is 0 (i.e., not paused/disabled), then call the secondary check.
    // Otherwise, return false immediately.
    uint flags = *(uint*)(*(int*)((char*)this + 0x5c) + 0x8e4); // m_pData->m_flags
    if ((flags >> 0x11 & 1) == 0) {
        // Secondary check (e.g., isAlive, isInRange, etc.)
        if (FUN_0078a7d0()) {
            return true;
        }
    }
    return false;
}