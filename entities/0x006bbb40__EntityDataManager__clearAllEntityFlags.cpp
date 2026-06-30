// FUNC_NAME: EntityDataManager::clearAllEntityFlags
void __fastcall EntityDataManager::clearAllEntityFlags(int this) {
    uint count = *(uint*)(this + 0xa4); // Number of entity entries (+0xa4)
    if (count != 0) {
        uint8_t* arrayBase = *(uint8_t**)(this + 0xa0); // Pointer to array of 0x18-byte entries (+0xa0)
        for (uint i = 0; i < count; ++i) {
            uint8_t* entry = arrayBase + (i * 0x18);
            int entityPtr = *(int*)entry; // +0x00: pointer to entity object
            // 0x48 is a sentinel for invalid/empty slots
            if (entityPtr != 0 && entityPtr != 0x48) {
                // Clear bit 25 (0x04000000) in entity flags at +0x14
                *(uint*)(entityPtr + 0x14) &= 0xfbffffff;
            }
        }
    }
    // Call internal update or notification function
    processAllEntityUpdates(); // FUN_006bb6d0
}