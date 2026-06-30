// FUN_00411840: EntityManager::addEntityToList
void EntityManager::addEntityToList(void* entity) {
    // Check if entity already in the list (max 32 slots at +0x14, count at +0x94)
    for (uint32_t i = 0; i < *(uint32_t*)(this + 0x94); i++) {
        if (*(void**)(this + 0x14 + i * 4) == entity) {
            // Already present – early return
            return;
        }
    }

    // Validate the entity and retrieve its data block
    void* entityData = getEntityData(entity); // FUN_004025a0
    if (entityData && *(int32_t*)(entityData + 0x60) >= 0) {
        // Clear/reset a field at +0x56 (e.g., flag, timer, or name buffer)
        resetEntityState(reinterpret_cast<uint8_t*>(entityData) + 0x56, 0x100); // FUN_00402920

        // Append the entity to the list if capacity allows
        if (*(uint32_t*)(this + 0x94) < 0x20) {
            *(void**)(this + 0x14 + *(uint32_t*)(this + 0x94) * 4) = entity;
            (*(uint32_t*)(this + 0x94))++;
        }
    }
}