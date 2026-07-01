// FUNC_NAME: ResourceManager::releaseAllPools
void __thiscall ResourceManager::releaseAllPools() {
    // Sub-pool at offset +0x20 (pointer to a management structure)
    SubPool* pool = *(SubPool**)((uint8_t*)this + 0x20);
    if (pool) {
        // Release countA items with type (6, 1, 0)
        int countA = *(int*)((uint8_t*)pool + 0xc);
        for (int i = 0; i < countA; i++) {
            releaseItemA(6, 1, 0); // e.g., deallocate resource type A
        }
        // Release countB items with parameter 1
        int countB = *(int*)((uint8_t*)pool + 0x18);
        for (int i = 0; i < countB; i++) {
            releaseItemB(1); // e.g., deallocate resource type B
        }
    }
}