// FUNC_NAME: EntityManager::processSpawnRequests
void EntityManager::processSpawnRequests(EntitySpawnList* thisList) {
    uint32_t index = 0;
    if (thisList->entityCount != 0) {
        do {
            // Check if the entity at current index has the "spawned" flag (bit 0 at offset 0x5F) cleared
            Entity* currentEntity = thisList->entityArray[index];
            if ((currentEntity->entityFlags & 0x1) == 0) {
                // Try to create a new entity instance
                void* newEntity = createEntity();
                if (newEntity != nullptr) {
                    // Initialize the newly created entity (call on member at offset 0x3C)
                    initializeEntity(newEntity + 0x3C);
                }
            }
            index++;
        } while (index < thisList->entityCount);
    }
}