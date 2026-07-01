// FUNC_NAME: EntityDataManager::createEntity

void __thiscall EntityDataManager::createEntity(int type, int data, uint8_t flags) {
    // Check if entity creation is currently allowed (global game state flag)
    char canCreate = checkGameState();
    if (canCreate != 0) {
        // Allocate 0x50 (80) bytes for entity data structure
        int* entity = allocateMemory(0x50);
        if (entity == nullptr) {
            entity = nullptr;
        } else {
            // Initialize the entity with the given type (calls internal constructor)
            entity = initializeEntity(type);
        }
        // Store flags and data at known offsets within the entity structure
        // +0x38: data (4 bytes)
        // +0x3c: flags (1 byte)
        *(int*)(entity + 0x38) = data;
        *(uint8_t*)(entity + 0x3c) = flags;
        // Prepare some temporary stack data for creation (likely a buffer or handle)
        prepareCreationStack(&temporary);
        // Register the newly created entity with the manager
        registerEntity(entity);
    }
    // Record profiling/debugging event (always called)
    debugProfileEnd();
}