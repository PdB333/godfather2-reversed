// FUNC_NAME: EntityDataManager::activateEntity
bool __thiscall EntityDataManager::activateEntity(EntityDataManager* this, EntityDataManager* entityManager, uint entityId)
{
    // Check for invalid ID
    if (entityId == 0xFFFFFFFF) {
        this->m_requestedId = 0xFFFFFFFF;  // +0x14
        this->m_loadedId = 0xFFFFFFFF;     // +0x18
        this->m_internalIndex = 0;         // +0x60
        return false;
    }

    // Access hash table from entityManager structure
    // entityManager+0x70 -> hash table header
    // header+0x30 -> hash table descriptor (pointer to bucket array, size)
    int* hashTableDesc = *(int**)(*(int*)(entityManager + 0x70) + 0x30);
    int* bucketArray = (int*)*hashTableDesc;          // base pointer
    int bucketSize = hashTableDesc[1];                // number of buckets
    uint bucketIndex = entityId % bucketSize;
    uint** entry = (uint**)*(bucketArray + bucketIndex * 4);

    uint internalIndex = 0;
    while (entry != nullptr) {
        if (*entry[0] == entityId) {
            // Found ID in hash table
            internalIndex = entry[2];                 // internal resource index
            break;
        }
        entry = (uint**)entry[3];                     // next entry (offset 12 bytes)
    }

    // If internal index found and entity validation succeeds
    if (internalIndex != 0) {
        char validationResult = this->validateEntity();  // FUN_005818d0
        if (validationResult != '\0') {
            // Set entity state
            this->m_internalIndex = internalIndex;      // +0x60
            this->m_flags |= 0x20020;                   // +0x10 (flags)
            this->m_requestedId = entityId;             // +0x14
            this->m_loadedId = entityId;                // +0x18
            this->m_loadState1 = 0;                     // +0x1c
            this->m_loadState2 = 0;                     // +0x20

            // Register as current entity in manager
            entityManager->m_currentEntity = (int)this; // +0x7c

            // Load entity resources (resource ID from offset +100 of this)
            EntityDataManager::loadEntityResources(entityManager, this->m_internalIndex, *(undefined4*)(this + 100), 1); // FUN_005918f0
            EntityDataManager::postLoadEntity(entityManager, this->m_internalIndex, *(undefined4*)(this + 100));          // FUN_00591880

            // Save previous state and finalize
            this->m_previousField = this->m_currentField; // +0x28 = +0x24
            entityManager->m_currentEntity = (int)this;   // +0x7c
            EntityDataManager::finalizeLoading();         // FUN_00591160
            this->m_currentField = 0;                     // +0x24
            return true;
        }
    }
    return false;
}