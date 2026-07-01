// FUNC_NAME: EntityManager::createAndRegisterEntity
void __thiscall EntityManager::createAndRegisterEntity(void* thisPtr, int entityType)
{
    char isReady;
    void* entity;

    // Check if system is initialized and ready (FUN_00481640)
    isReady = isSystemReady();
    if (isReady != 0) {
        // Attempt to allocate a new entity slot (FUN_009c8e50 with size 0x40 = 64 bytes)
        entity = allocateMemory(0x40);
        if (entity != (void*)0x0) {
            // Initialize the entity using this manager (FUN_008a9bd0)
            entity = initializeNewEntity(thisPtr);
            // Store the provided entity type at offset +0x38 (likely m_entityType or m_id)
            *(int*)((char*)entity + 0x38) = entityType;
            // Register the entity with the world/system (FUN_00481690)
            registerEntity(entity);
            return;
        }
        // Fallback: if allocation failed, store entity type globally and register null
        g_lastEntityType = entityType;
        registerEntity((void*)0x0);
    }
}