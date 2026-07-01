// FUNC_NAME: EntityManager::setEntityState
void __thiscall EntityManager::setEntityState(void* this, int entityID, char newState) {
    int index = findEntityIndex(entityID);
    if (index >= 0) {
        // baseArray = *(int*)(this + 0x60) — pointer to an array of entity pointers
        // Each entry is 8 bytes; the pointer to the entity is at offset 4 inside each entry
        int entityPtr = *(int*)(*(int*)((char*)this + 0x60) + 4 + index * 8);
        if (*(char*)(entityPtr + 0x1dc) != newState) {
            // +0x1d8: last state change timestamp (set to global timestamp)
            *(int*)(entityPtr + 0x1d8) = g_CurrentTimestamp;
            // +0x1dc: current state byte (e.g., animation state, AI state)
            *(char*)(entityPtr + 0x1dc) = newState;
        }
    }
}