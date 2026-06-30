// FUNC_NAME: EntityManager::getActionStatusByID
uint8_t __thiscall EntityManager::getActionStatusByID(int thisPtr, int32_t param2, int32_t id) {
    uint8_t result = 0;
    mutexLock(&g_mutex);

    uint32_t count = *(uint32_t*)(thisPtr + 0x20); // +0x20: number of entries
    if (count != 0) {
        uint32_t index = 0;
        int* entryBase = *(int**)(thisPtr + 0x1c); // +0x1c: pointer to array of entries (0x28 each)
        while (true) {
            // Each entry structure:
            // +0x10: entity ID (int32_t)
            // +0x14: action/state value (unknown, used in evaluateEntryCondition)
            if (*(int32_t*)(entryBase + 0x10) == id) {
                result = evaluateEntryCondition(id, *(uint32_t*)(entryBase + 0x14));
                break;
            }
            index++;
            entryBase += 0x28; // move to next entry (0x28 bytes per entry)
            if (index >= count) {
                break;
            }
        }
    }

    mutexUnlock(&g_mutex);
    return result;
}