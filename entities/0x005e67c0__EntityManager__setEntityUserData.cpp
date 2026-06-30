// FUNC_NAME: EntityManager::setEntityUserData
extern uint8_t * g_slotManagerBase; // DAT_012234bc, base of entity slot array

uint8_t EntityManager::setEntityUserData(uint slotId, uint32_t data) {
    uint8_t success = 0;
    uint16_t index = (uint16_t)(slotId & 0xFFFF);
    if (index < 0x200) {
        // Slot layout: header 0x10 bytes, then array of 0x30-byte entries
        uint8_t *slotPtr = g_slotManagerBase + 0x10 + index * 0x30;
        if (slotPtr != nullptr) {
            // Verify slot ID at offset +0x2C
            uint32_t storedId = *(uint32_t *)(slotPtr + 0x2C);
            if (storedId == slotId) {
                // Pointer to entity object is at offset +0x10
                void *entityPtr = *(void **)(slotPtr + 0x10);
                if (entityPtr != nullptr) {
                    // Write user data to entity at offset +0x5C
                    *(uint32_t *)((uint8_t *)entityPtr + 0x5C) = data;
                    success = 1;
                }
            }
        }
    }
    return success;
}