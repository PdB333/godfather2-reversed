// FUNC_NAME: EntityDataManager::getEntityData
void* __thiscall EntityDataManager::getEntityData(uint entityID) {
    // Use default entity ID if caller sent the invalid sentinel
    if (entityID == 0xFFFFFFFF) {
        entityID = this->m_defaultEntityID; // +0x3c
    }

    // Validate index against the current count of loaded entities
    // m_dataArray points to a structure at +0x20, which contains count (+0xa4) and pool base (+0xac)
    EntityDataArray* dataArray = *(EntityDataArray**)((int)this + 0x20);
    if (entityID < dataArray->m_count) {
        // Each entity data is 0x61 bytes, starting at pool base + 0x40 (skip pool header)
        return (void*)(entityID * 0x61 + (int)dataArray->m_poolBase + 0x40);
    }

    // Return a sentinel null object (global invalid entity data)
    return (void*)&g_invalidEntityData; // DAT_012222a0
}